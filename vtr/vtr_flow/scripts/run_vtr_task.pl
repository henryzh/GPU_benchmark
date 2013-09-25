#!/usr/bin/perl
###################################################################################
# This script executes one or more VTR tasks
#
# Usage:
#	run_vtr_task.pl <task_name1> <task_name2> ... [OPTIONS]
#
# Options:
# 	-p <N>:  Perform parallel execution using N threads. Note: Large benchmarks 
#				will use very large amounts of memory (several gigabytes). Because 
#				of this, parallel execution often saturates the physical memory, 
#				requiring the use of swap memory, which will cause slower 
#				execution. Be sure you have allocated a sufficiently large swap 
#				memory or errors may result. 
#	-l <task_list_file>:  A file containing a list of tasks to execute. Each task 
#							name should be on a separate line.
#
#	-hide_runtime: Do not show runtime estimates
#
# Note: At least one task must be specified, either directly as a parameter or 
#		through the -l option.
###################################################################################

use strict;
use Cwd;
use File::Spec;
use threads;
use Thread::Queue;
use POSIX qw(strftime);


# Function Prototypes
sub trim;
sub run_single_task;
sub do_work;
sub ret_expected_runtime;

# Get Absoluate Path of 'vtr_flow
Cwd::abs_path($0) =~ m/(.*vtr_flow)/;
my $vtr_flow_path = $1;

my @tasks;
my @task_files;
my $token;
my $processors = 1;
my $run_prefix = "run";
my $show_runtime_estimates = 1;

# Parse Input Arguments
while ($token = shift(@ARGV))
{
	# Check for -pN
	if ($token =~ /^-p(\d+)$/)
	{
		$processors = int($1);
	}
	
	# Check for -p N
	elsif ($token eq "-p")
	{
		$processors = int(shift(@ARGV));
	}
	
	# Check for a task list file
	elsif ($token =~ /^-l(.+)$/)
	{
		push(@task_files, expand_user_path($1));
	}
	elsif ($token eq "-l")
	{
		push(@task_files, expand_user_path(shift(@ARGV)));
	}
	
	elsif ($token eq "-hide_runtime")
	{
		$show_runtime_estimates = 0;
	}
	
	elsif ($token =~ /^-/)
	{
		die "Invalid option: $token\n";
	}
	
	# must be a task name
	else
	{
		push(@tasks, $token);	
	}	
}

# Read Task Files
foreach(@task_files)
{
	open (FH, $_) or die "$! ($_)\n";
	while (<FH>)
	{
		push(@tasks, $_);
	}
	close (FH);
}

# Remove duplicate tasks
my %hash = map {$_, 1} @tasks;
@tasks = keys %hash;

#print "Processors: $processors\n";
#print "Tasks: @tasks\n";

if ($#tasks == -1)
{
	die "\n" .
		"Incorect usage.  You must specify at least one task to execute\n" .
		"\n" .
		"USAGE:\n" .
		"run_vtr_task.pl <TASK1> <TASK2> ... \n" .
		"\n" . 
		"OPTIONS:\n" .
		"-l <path_to_task_list.txt> - Provides a text file with a list of tasks\n" .
		"-p <N> - Execution is performed in parallel using N threads (Default: 1)\n";
}

##############################################################
# Run tasks
##############################################################

foreach my $task (@tasks)
{
	run_single_task ($task);	
}


##############################################################
# Subroutines
##############################################################

sub run_single_task
{
	my $circuits_dir;
	my $archs_dir;
	my $script_default = "run_vtr_flow.pl";
	my $script = $script_default;
	my $script_path;
	my $script_params = "";
	my @circuits;
	my @archs;
	
	my $task = shift(@_);	
	my $task_dir = "$vtr_flow_path/tasks/$task";
	chdir ($task_dir) or die "Task directory does not exist ($task_dir): $!";
	
	print "\n$task\n";
	print "--------------------\n";
	
	# Get Task Config Info
	
	my $task_config_file_path ="config/config.txt";
	open (CONFIG_FH, $task_config_file_path) or die "$! ($task_config_file_path)";
	while (<CONFIG_FH>)
	{
		my $line = $_;
		chomp($line);
		
		if ($line =~ /^\s*#.*$/ or $line =~ /^\s*$/) {next;}
		
		my @data = split(/=/, $line);
		my $key = trim($data[0]);
		my $value = trim($data[1]);
		if ($key eq "circuits_dir")
		{
			$circuits_dir = $value;
		}
		elsif ($key eq "archs_dir")
		{
			$archs_dir = $value;
		}
		elsif ($key eq "circuit_list_add")
		{
			push (@circuits, $value);
		}
		elsif ($key eq "arch_list_add")
		{
			push (@archs, $value);
		}
		elsif ($key eq "script_path")
		{
			$script = $value;
		}
		elsif ($key eq "script_params")
		{
			$script_params = $value;
		}
	}
	
	# Using default script
	if ($script eq $script_default)
	{				
		# This is hack to automatically add the option '-temp_dir .' if using the run_vtr_flow.pl script
		# This ensures that a 'temp' folder is not created in each circuit directory
		if (! ($script_params =~ /-temp_dir/))
		{
			$script_params = $script_params . " -temp_dir . "
		}
	}
	else
	{
		$show_runtime_estimates = 0;
	}
	
	$circuits_dir = expand_user_path($circuits_dir);
	$archs_dir = expand_user_path($archs_dir);

	if (-d "$vtr_flow_path/$circuits_dir")
	{
		$circuits_dir = "$vtr_flow_path/$circuits_dir";
	}
	elsif (-d $circuits_dir)
	{
	}
	else
	{
		die "Circuits directory not found ($circuits_dir)";
	}
	
	if (-d "$vtr_flow_path/$archs_dir")
	{
		$archs_dir = "$vtr_flow_path/$archs_dir";
	}
	elsif (-d $archs_dir)
	{
	}
	else
	{
		die "Archs directory not found ($archs_dir)";
	}
	
	(@circuits) or die "No circuits specified for task $task";
	(@archs) or die "No architectures specified for task $task";
	
	$script = expand_user_path($script);
	if (-e "$task_dir/config/$script")
	{
		$script_path = "$task_dir/config/$script";
	}
	elsif (-e "$vtr_flow_path/scripts/$script")
	{
		$script_path = "$vtr_flow_path/scripts/$script";
	}
	elsif (-e $script)
	{
	}
	else
	{
		die "Cannot find script for task $task ($script).  Looked for $task_dir/config/$script or $vtr_flow_path/scripts/$script";
	}
	
	# Check if golden file exists
	my $golden_results_file = "$task_dir/config/golden_results.txt";
	if ($show_runtime_estimates)
	{
		if (not -r $golden_results_file)
		{
			$show_runtime_estimates = 0;
		}
	}
	
	##############################################################
	# Create a new experiment directory to run experiment in
	# Counts up until directory number doesn't exist
	##############################################################
	my $experiment_number = 1;
	
	while(-e "$run_prefix$experiment_number") {
	    ++$experiment_number;
	}
	mkdir ("$run_prefix$experiment_number", 0775) or die "Failed to make directory ($run_prefix$experiment_number): $!";
	chmod(0775, "$run_prefix$experiment_number");
	chdir ("$run_prefix$experiment_number") or die "Failed to change to directory ($run_prefix$experiment_number): $!";
	
	# Create the directory structure
	# Make this seperately from file script just in case failure occurs creating directory
	foreach my $arch (@archs) 
	{
	    mkdir("$arch", 0775) or die "Failed to create directory ($arch): $!";
	    chmod(0775, "$arch");
	    foreach my $circuit (@circuits) 
	    {
	        mkdir("$arch/$circuit", 0775) or die "Failed to create directory $arch/$circuit: $!";
	        chmod(0775, "$arch/$circuit");
	    }
	}
	
	##############################################################
	# Run experiment
	##############################################################
	if ($processors == 1) 
	{
	    foreach my $circuit (@circuits) 
	    {
	        foreach my $arch (@archs) 
	        {
	        	if ($show_runtime_estimates)
	        	{
	        		my $runtime = ret_expected_runtime($circuit, $arch, $golden_results_file);
	        		print strftime "Current time: %b-%d %I:%M %p.  ", localtime;	
	        		print "Expected runtime of next benchmark: " . $runtime . "\n";
	        	}
	        	
	            chdir("$task_dir/$run_prefix${experiment_number}/${arch}/${circuit}"); # or die "Cannot change to directory $StartDir/$run_prefix${experiment_number}/${arch}/${circuit}: $!";
				system("$script_path $circuits_dir/$circuit $archs_dir/$arch $script_params\n");
	        }
	    }
	} 
	else
	{
		my $thread_work = Thread::Queue->new();	
		my $thread_result = Thread::Queue->new();
		my $threads = $processors;
		#print "# of Threads: $threads\n";
		
		foreach my $circuit (@circuits) 
		{
	        foreach my $arch (@archs) 
	        {        	
	        	my $dir = "$task_dir/$run_prefix${experiment_number}/${arch}/${circuit}";
	        	my $command = "$script_path $circuits_dir/$circuit $archs_dir/$arch $script_params";
	        	$thread_work->enqueue("$dir||||$command");            
	        }
	    }
		
		my @pool = map
		{
			threads->create(\&do_work, $thread_work, $thread_result)
		} 1..$threads;
		
		
		for (1 .. $threads)
		{
			while (my $result = $thread_result->dequeue)
			{
				chomp($result);
				print $result . "\n";
			}
		}
		
		$_->join for @pool;	
	}
}

sub do_work
{
	my ($work_queue, $return_queue) = @_;
	my $tid = threads->tid;
	
	
	while (1)
	{
		my $work = $work_queue->dequeue_nb();
		my @work = split(/\|\|\|\|/, $work);
		my $dir = @work[0];
		my $command = @work[1];
		
		if (! $dir)
		{
			last;
		}

		system "cd $dir; $command > thread_${tid}.out";
		open(OUT_FILE, 	"$dir/thread_${tid}.out") or die "Cannot open $dir/thread_${tid}.out: $!";
		my $sys_output = do { local $/; <OUT_FILE> };
		
		
		#$sys_output =~ s/\n//g;
		$return_queue->enqueue($sys_output);			
	}	
	$return_queue->enqueue(undef);
	#print "$tid exited loop\n"
}

# trim whitespace
sub trim($)
{
    my $string = shift;
    $string =~ s/^\s+//;
    $string =~ s/\s+$//;
    return $string;
}

sub expand_user_path
{
	my $str = shift;	
	$str =~ s/^~\//$ENV{"HOME"}\//;
	return $str;
}

sub ret_expected_runtime
{
	my $circuit_name = shift;
	my $arch_name = shift;
	my $golden_results_file_path = shift;
	my $seconds = 0;
	
	open(GOLDEN, $golden_results_file_path);
	my @lines = <GOLDEN>;
	close(GOLDEN);
	
	my $header_line = shift(@lines);
	my @headers = split(/\s+/, $header_line);
	 
	my %index;
	@index{@headers} = (0..$#headers);
	
	my @line_array;
	my $found = 0;
	foreach my $line (@lines)
	{
		@line_array = split(/\s+/, $line);
		if ($arch_name eq @line_array[0] and $circuit_name eq @line_array[1])
		{
			$found = 1;
			last;
		}
	}
	
	if (not $found)
	{
		return "Unknown";
	}
	
	my $location = $index{"pack_time"};
	if ($location)
	{
		$seconds += @line_array[$location];		
	}
	my $location = $index{"place_time"};
	if ($location)
	{
		$seconds += @line_array[$location];		
	}
	my $location = $index{"min_chan_width_route_time"};
	if ($location)
	{
		$seconds += @line_array[$location];		
	}
	my $location = $index{"crit_path_route_time"};
	if ($location)
	{
		$seconds += @line_array[$location];		
	}
	my $location = $index{"route_time"};
	if ($location)
	{
		$seconds += @line_array[$location];		
	}
	
	if ($seconds != 0)
	{
		if ($seconds < 60)
		{		
			my $str = sprintf("%.0f seconds", $seconds);
			return $str;
		}
		elsif ($seconds < 3600)
		{
			my $min = $seconds / 60;
			my $str = sprintf("%.0f minutes", $min);
			return $str;
		}
		else
		{
			my $hour = $seconds / 60 / 60;
			my $str = sprintf("%.0f hours", $hour);
			return $str;
		}
	}
	else
	{
		return "Unknown";
	}
}
