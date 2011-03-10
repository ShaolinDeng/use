#use strict;
while(<DATA>)
{
	if(/^#/)
	{
		next;
	}
	my @grades=split /[ \t]+/,$_;
	my $name=shift @grades;
	my $ave =($grades[0]+$grades[1]+$grades[2])/3;
	print "student $name Average $ave\n";
}
__DATA__
#student  grade grade grade

li         98     95    92
ming       75    84   99
neng       45    26    55
