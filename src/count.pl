#!/usr/bin/env perl
use strict;
use warnings;

die "Usage: $0 <words to search for> ...\n" if @ARGV < 1;

my @NAMES = @ARGV;
my %COUNTS;
my $line;

while($line = <STDIN>) {
	$COUNTS{$_} += () = $line =~ /$_/g foreach(@NAMES);
}

printf "`$_' matched %d times\n", ($COUNTS{$_} || 0) foreach(@NAMES);
