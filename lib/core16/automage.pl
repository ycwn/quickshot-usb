#!/usr/bin/perl -w
#


use strict;
use Getopt::Long;


my $cache  = "automage.cache";
my $generate;
my $processor = $ENV{'CPP'};
my $quiet;


GetOptions(
    "cache=s"     => \$cache,
    "generate"    => \$generate,
    "processor=s" => \$processor,
    "quiet"       => \$quiet);


if ($generate) {

    open CACHE, ">", $cache;

    print CACHE "\n";
    print CACHE "#\n";
    print CACHE "# Automatically generated automagic cache.\n";
    print CACHE "# Do not edit.\n";
    print CACHE "#\n";
    print CACHE "\n";
    print CACHE "\n";

    foreach my $source (@ARGV) {

	print $processor, " -DAUTOMAGIC ", $source, "\n" if (!$quiet);
	open SOURCE, "-|", $processor . " -DAUTOMAGIC " . $source or die "$!";

	while (<SOURCE>) {

	    print CACHE $1, "\n" while (/automagic\((.*?)\)/g);

	}

	close SOURCE;
    }

    print CACHE "\n";
    print CACHE "\n";

    close CACHE;

    exit 0;

}


my $input  = shift(@ARGV);
my $output = shift(@ARGV);

my @magic_list  = ();
my @summon_list = ();

my $summon_code;
my $summon_mode;
my $summon_name;

my $line_no;
my $invocations;
my $comment;


if ($output =~ /\.asm$/) {

    $comment = ";";

} elsif ($output =~ /\.c$/) {

    $comment = "//";

} else {

    $comment = "#";

}



#
# Process the cache
#

open CACHE, "<", $cache;

while (<CACHE>) {

    chomp $_;

    next if (/^#.*|^\s*$/);

    push @magic_list, [ map {s/^\s+|\s+$//g; $_;} split(/,/) ];

}

close CACHE;


#
# Summon magic and generate output
#

open IN,  "<", $input;
open OUT, ">", $output;

$summon_code = "";
$summon_mode = 0;
$summon_name = "";

$line_no     = 1;
$invocations = 0;

while (<IN>) {

    chomp $_;

    if (/^#summon\s+(\w+)(\s*(.*))?/) {

	die $input, ", line ", $line_no, ": Duplicate summon\n" if $summon_mode != 0;

	$summon_code = "";
	$summon_mode = 1;
	$summon_name = $1;

	@summon_list = map {[@$_[1..$#$_]]} grep {$_->[0] eq $summon_name} @magic_list;

	foreach my $op (map {s/^\s+|\s+$//g; $_;} split(/,/, $2)) {

	    if ($op =~ /^#.*|^\s*$/) {

		next;

	    } elsif ($op =~ /sort\( *(\d+) *\)/) {

 		@summon_list = sort {$a->[$1] cmp $b->[$1]} @summon_list;

	    } elsif ($op =~ /order\( *(\d+) *\)/) {

 		@summon_list = sort {$a->[$1] <=> $b->[$1]} @summon_list;

	    } elsif ($op =~ /reverse/) {

		@summon_list = reverse @summon_list;

	    }

	}

    } elsif (/^#done/) {

	die $input, ", line ", $line_no, ": Missing summon\n" if ($summon_mode == 0);

	if ($#summon_list >= 0) {

	    print OUT $comment, " Invocation of ", $summon_name, " magic\n";

	    foreach (@summon_list) {

		my $code = $summon_code;

		$code =~ s/\@magic\[(\d+)\]/$_->[$1]/meg;

		print OUT $code;

	    }

	    $invocations++;

	} else {

	    print OUT $comment, " No invocation of ", $summon_name, " magic\n";

	}

	$summon_mode = 0;

    } else {

	if ($summon_mode) {

	    $summon_code .= $_ . "\n" unless (/^[ \t]*$/);

	} else {

	    print OUT $_, "\n";

	}

    }

    $line_no++;

}

close OUT;
close IN;


print $output, ": ", $invocations, " invocation", ($invocations == 1)? "\n": "s\n";

