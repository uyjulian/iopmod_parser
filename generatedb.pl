#!/usr/bin/perl
use strict;

my $debug = 0;

foreach my $file (@ARGV) {
	print "Reading file " . $file . "\n" if $debug;
	open(infile, $file);
	my $module = "";
	while(<infile>) {
		print $_ . "\n" if $debug;
		if ($_ =~ / ([^ ]*)_IMPORTS_start/) {
			print $1 . "\n" if $debug;
			$module = $1;
		}
		if ($_ =~ /DECLARE_IMPORT\(([0-9]*) *, *([^\)]*)/) {
			print " [\"" . $module . "\", " . $1 . ", \"" . $2 ."\"],\n";
		}
	}
	close(infile);
}

