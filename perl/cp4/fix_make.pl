use strict;
use warnings;
while(1){
	my $line=<STDIN>;
	if (not defined($line)){
		last;
	}
	chomp $line;

	$line=~s/^        /\t/;
	$line=~s/\\\s*/\\/;
	print "$line\n";
}

