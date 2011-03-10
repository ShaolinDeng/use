use strict;
use warnings;

my @strings=(
"#starts with a hash",
"this is one's got nothings",
"there is # in the middle",
"one at the end#",
"two # in the # line",
"no hash");
my $i;
for($i=0;i<=$#strings; $i++)
{
	if($strings[$i]=~/#/)
	{
		print "comment:$strings[$i]\n";
	}else{
		print "code:$strings[$i]\n";
	}
}
