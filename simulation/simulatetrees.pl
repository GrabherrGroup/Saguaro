#!/usr/bin/perl

#  simulatetree.pl
#  Generate config files for dawg to simulate sequences using the trees given in the config file.

# Input parameters
my $boundaries_file = $ARGV[0];
my $parts=$ARGV[1];
my $config_file = $ARGV[2];

my %cons=();
my %conl=();
my %conh=();

my $treeprob=0;
my $tree=0;
#read in configuration
open(CON, $config_file);

while($z=<CON>) {
chomp $z;
@convals=split('\t',$z);
$conlv=$treeprob;
$treeprob=$treeprob+($convals[0]*100);
$conhv=$treeprob;
$tree++;
if($treeprob>100){print "Probabilities need to add upto one. Invalid config file.";exit;}
else{$cons{$tree}=$convals[1];$conh{$tree}=$conhv;$conl{$tree}=$conlv;}
}

close CON;

if($treeprob!=100){print "Probabilities need to add upto one. Invalid config file.";exit;}


open(IN, $boundaries_file);
my $count=0;

while($z=<IN>) {
$phylogeny=0;
$phylogenyprob=int(rand(99))+1;$count++;
if($count>$parts){exit();}
chomp $z;$z2=<IN>;chomp $z2;
$lenseq=$z2-$z+1;
while($phylogeny==0){
	for($i=0;$i<=$tree;$i++){
		if(($phylogenyprob>$conl{$i})&&($phylogenyprob<=$conh{$i})){$phylogeny=$i;$treetext=$cons{$i}}
		}
	}
#write dawg config files
		open(OUT2, ">simfiles/example$count");
		print OUT2 "Tree   = $treetext\n";
		print OUT2 "Length = $lenseq\n";
		print OUT2 "File = \"simfasta/example$count.Fasta\"\n";
		print OUT2 "Model  = \"GTR\"\nParams = {1.5, 3.0, 0.9, 1.2, 2.5, 1.0}\nFreqs  = {0.20, 0.30, 0.30, 0.20}\nReps = 1\nFormat = \"Fasta\"\n";
		close OUT2;
print "$z\t$phylogeny\n";print "$z2\t$phylogeny\n";print "NA\t$phylogeny\n";
}





