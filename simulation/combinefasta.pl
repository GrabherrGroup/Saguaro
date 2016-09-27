#!/usr/bin/perl

# combinefasta.pl
# Combines multiple fasta sequences into a single fasta sequence by concatinating sequences. 



# Input parameters
my $genome_file = $ARGV[0];
my $seqs = {SEQ =>my $genename};

open(FASTA, $genome_file);

while($line = <FASTA>){

if($line=~ /^>/){
if($header){
$header=~s/>//;
$seqs{$header}{SEQ}=$seqst_temp;
}
chomp $line;
$header="";
$line =~ s/[\s]/_/g;
$header=$line;
$seqst_temp="";

}
else{
$line =~ s/[\n\t\f\r_0-9\s]//g;
$seqst_temp .= $line;
}

}#end of while loop
if($header){
$header=~s/>//;
$seqs{$header}{SEQ}=$seqst_temp;
}

close FASTA;

foreach $iso (sort keys %seqs) {
print "$iso\n";
open(OUT, ">>$iso.genomes");
print OUT "$seqs{$iso}{SEQ}";
close OUT;
}

