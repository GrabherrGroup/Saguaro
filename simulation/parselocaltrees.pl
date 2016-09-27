#!/usr/bin/perl

#  parselocaltrees.pl
#  Parse the LocalTrees.out file from Saguaro, find nearest tree using tpod and write tree for each region identified.

use List::Util qw[min max];

# Input parameters
my $local_file = $ARGV[0];

$treenum=$ARGV[2];

$indv=$ARGV[3];

open(IN, $local_file);
$count=0;

while($z=<IN>) {

	if($z=~m/score/){$count++;
	chomp $z;
	@values=split(/\s+/,$z);

	$start=$values[2];
	$end=$values[4];

	$z=<IN>;#read in header
open(FITCHIN,">infile");

	print FITCHIN "$indv\n";
	#read in 10 lines 	#write infile for fitch
for($j=1;$j<=$indv;$j++){
	$z=<IN>;chomp $z;@matrixrow=split(/\t/,$z);
	print FITCHIN "$matrixrow[0]          ";
	for($i=1;$i<$indv;$i++){print FITCHIN "$matrixrow[$i] ";}
	print FITCHIN "$matrixrow[$indv]\n";
}

close FITCHIN;
		#run fitch
		system("fitch < param_file");
		$newtree=$count . "tree";
		system("cat outtree|tr -d '\n'>$newtree");
		unlink "outfile";
		unlink "outtree";

	for($i=1;$i<=$treenum;$i++){system("cat before.tree$i $newtree > tree$i.test");}
	
	unlink $newtree;

		#run TOPD against each of the trees
	for($i=1;$i<=$treenum;$i++){
		$treecompare=$count . "treecompare$i";
		system("topd_v3.3.pl -f tree$i.test -out $treecompare");unlink "tree$i.test";
		}
		#find nearest tree
	%def=();

	for($i=1;$i<=$treenum;$i++){		
	$treecompare=$count . "treecompare$i";
	open(COMP,$treecompare);
	while($c1=<COMP>){if($c1=~m/Split/){chomp $c1;@values4=split(/\s+/,$c1);$def{$i}=$values4[6];$c1p=<COMP>;@values4=split(/\s+/,$c1p);}}
	close COMP;
	unlink $treecompare;
	}

	$mindef=$def{1};

	for($i=1;$i<=$treenum;$i++){if($def{$i}<$mindef){$mindef=$def{$i};}}

	#print positions of block and the nearest tree
	open(LOCALTOUT,">>$ARGV[1]");
	$geti=0;$icount=0;
	for($i=1;$i<=$treenum;$i++){#print LOCALTOUT "$i\t$mindef\t$def{$i}\n";
	if($def{$i}==$mindef){
		if($icount>1){print LOCALTOUT "$start\t0\t$mindef\n";print LOCALTOUT "$end\t0\t$mindef\n";print LOCALTOUT "NA\t0\t$mindef\n";$i=$treenum+1;}
		else{$geti=$i;$icount++;}
		}
	}

	if($icount==1){print LOCALTOUT "$start\t$geti\t$mindef\n";
			print LOCALTOUT "$end\t$geti\t$mindef\n";
			print LOCALTOUT "NA\t$geti\t$mindef\n";
			}

	close LOCALTOUT;
}#end of score if

}#end of file while

close IN;





