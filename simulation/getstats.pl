#!/usr/bin/perl

use List::Util qw[min max];

# Input parameters
my $boundaries_file = $ARGV[0];
my $prediction_file = $ARGV[1];

open(IN, $boundaries_file);
%truth=();
while($z=<IN>) {chomp $z;@values1=split(/\t/,$z);
		$z=<IN>;chomp $z;@values2=split(/\t/,$z);
		for($i=$values1[0];$i<=$values2[0];$i++){$truth{$i}=$values1[1];}
		$z=<IN>;#blank
}#end of file while
$genomelength=$values2[0];

close IN;

$count=0;
$distsum=0;
open(IN, $prediction_file);
%prediction=();
while($z=<IN>) {chomp $z;@values1=split(/\t/,$z);
		$z=<IN>;chomp $z;@values2=split(/\t/,$z);
		for($i=$values1[0];$i<=$values2[0];$i++){$prediction{$i}=$values1[1];}
		$z=<IN>;#blank
		$count++;$distsum=$distsum+($values1[2]*($values2[0]-$values1[0]));
}#end of file while
close IN;

$meandist=$distsum/($count*$genomelength);

$correctcluster=0;
$wrongcluster=0;
$nocluster=0;

for($i=1;$i<=$genomelength;$i++){
if(!(exists $prediction{$i})){$nocluster++;}
elsif($truth{$i}==$prediction{$i}){$correctcluster++;}
else{$wrongcluster++;}
#print "$i\t$truth{$i}\t$prediction{$i}\t$correctcluster\t$wrongcluster\t$nocluster\n";
#print "$meandist\n";
}

print "$genomelength\t$correctcluster\t$wrongcluster\t$nocluster\t$meandist\n";


