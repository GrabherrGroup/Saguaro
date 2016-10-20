cmake_minimum_required(VERSION 3.3)
project(saguaro)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread -std=c++14 -O3 -w")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

# Saguaro binaries
set(SOURCE_FILES_CACTICORRELATE ryggrad/base/ErrorHandling.cc ryggrad/base/FileParser.cc ryggrad/base/StringUtil.cc src/CactiCorrelate.cc ryggrad/util/mutil.cc) 
set(SOURCE_FILES_CHROMOPAINTCACTI ryggrad/base/ErrorHandling.cc ryggrad/base/FileParser.cc ryggrad/base/StringUtil.cc src/ChromoPaintCacti.cc src/DNAVector.cc ryggrad/util/mutil.cc ryggrad/visual/Color.cc ryggrad/visual/Eps.cc) 
set(SOURCE_FILES_CLUSTERCACTI ryggrad/base/ErrorHandling.cc ryggrad/base/FileParser.cc ryggrad/base/StringUtil.cc src/Cactus.cc src/ClusterCacti.cc ryggrad/util/mutil.cc) 
set(SOURCE_FILES_FASTA2HMMFEATURE ryggrad/base/ErrorHandling.cc ryggrad/base/FileParser.cc ryggrad/base/StringUtil.cc src/DNAVector.cc src/Fasta2HMMFeature.cc src/HMMDistance.cc ryggrad/util/mutil.cc) 
set(SOURCE_FILES_FILTERCACTI ryggrad/base/ErrorHandling.cc ryggrad/base/FileParser.cc ryggrad/base/StringUtil.cc src/Cactus.cc src/FilterCacti.cc ryggrad/util/mutil.cc) 
set(SOURCE_FILES_FILTERFEATURES ryggrad/base/ErrorHandling.cc ryggrad/base/FileParser.cc ryggrad/base/StringUtil.cc src/DNAVector.cc src/FilterFeatures.cc src/HMMDistance.cc ryggrad/util/mutil.cc) 
set(SOURCE_FILES_FREQ2HMMFEATURE ryggrad/base/ErrorHandling.cc ryggrad/base/FileParser.cc ryggrad/base/StringUtil.cc src/DNAVector.cc src/Freq2HMMFeature.cc src/HMMDistance.cc ryggrad/util/mutil.cc) 
set(SOURCE_FILES_GENOTYPE2HMMFEATURE ryggrad/base/ErrorHandling.cc ryggrad/base/FileParser.cc ryggrad/base/StringUtil.cc src/DNAVector.cc src/Genotype2HMMFeature.cc src/HMMDistance.cc ryggrad/util/mutil.cc)
set(SOURCE_FILES_HMMCLASSIFY  ryggrad/base/ErrorHandling.cc ryggrad/base/FileParser.cc ryggrad/base/StringUtil.cc src/HMMClassify.cc src/HMMDecode.cc ryggrad/util/mutil.cc) 
set(SOURCE_FILES_HMMTRAIN ryggrad/base/ErrorHandling.cc ryggrad/base/FileParser.cc ryggrad/base/StringUtil.cc src/HMMDecode.cc src/HMMDistance.cc src/HMMTrain.cc src/SOM.cc ryggrad/util/mutil.cc) 
set(SOURCE_FILES_LOCALTREES ryggrad/base/ErrorHandling.cc ryggrad/base/FileParser.cc ryggrad/base/StringUtil.cc src/HMMDecode.cc src/HMMDistance.cc src/LocalTrees.cc src/SOM.cc ryggrad/util/mutil.cc) 
set(SOURCE_FILES_MAF2HMMFEATURE ryggrad/base/ErrorHandling.cc ryggrad/base/FileParser.cc ryggrad/base/StringUtil.cc src/DNAVector.cc src/HMMDistance.cc src/Maf2HMMFeature.cc ryggrad/util/mutil.cc) 
set(SOURCE_FILES_PULLFROMFASTA ryggrad/base/ErrorHandling.cc ryggrad/base/FileParser.cc ryggrad/base/StringUtil.cc src/DNAVector.cc src/PullFromFasta.cc ryggrad/util/mutil.cc) 
set(SOURCE_FILES_SAGUARO ryggrad/base/ErrorHandling.cc ryggrad/base/FileParser.cc ryggrad/base/StringUtil.cc src/DNAVector.cc src/HMMDecode.cc src/HMMDistance.cc src/Saguaro.cc ryggrad/util/mutil.cc) 
set(SOURCE_FILES_SAGUARO2PHYLIP ryggrad/base/ErrorHandling.cc ryggrad/base/FileParser.cc ryggrad/base/StringUtil.cc src/Saguaro2Phylip.cc ryggrad/util/mutil.cc) 
set(SOURCE_FILES_SORTCACTUS ryggrad/base/ErrorHandling.cc ryggrad/base/FileParser.cc ryggrad/base/StringUtil.cc src/SortCactus.cc ryggrad/util/mutil.cc) 
set(SOURCE_FILES_VCF2HMMFEATURE ryggrad/base/ErrorHandling.cc ryggrad/base/FileParser.cc ryggrad/base/StringUtil.cc src/DNAVector.cc src/HMMDistance.cc src/VCF2HMMFeature.cc ryggrad/util/mutil.cc) 

add_executable(CactiCorrelate ${SOURCE_FILES_CACTICORRELATE})
add_executable(ChromoPaintCacti ${SOURCE_FILES_CHROMOPAINTCACTI})
add_executable(ClusterCacti ${SOURCE_FILES_CLUSTERCACTI})
add_executable(Fasta2HMMFeature ${SOURCE_FILES_FASTA2HMMFEATURE})
add_executable(FilterCacti ${SOURCE_FILES_FILTERCACTI})
add_executable(FilterFeatures ${SOURCE_FILES_FILTERFEATURES})
add_executable(Freq2HMMFeature ${SOURCE_FILES_FREQ2HMMFEATURE})
add_executable(Genotype2HMMFeature ${SOURCE_FILES_GENOTYPE2HMMFEATURE})
add_executable(HMMClassify ${SOURCE_FILES_HMMCLASSIFY})
add_executable(HMMTrain ${SOURCE_FILES_HMMTRAIN})
add_executable(LocalTrees ${SOURCE_FILES_LOCALTREES})
add_executable(Maf2HMMFeature ${SOURCE_FILES_MAF2HMMFEATURE})
add_executable(PullFromFasta ${SOURCE_FILES_PULLFROMFASTA})
add_executable(Saguaro ${SOURCE_FILES_SAGUARO})
add_executable(Saguaro2Phylip ${SOURCE_FILES_SAGUARO2PHYLIP})
add_executable(SortCactus ${SOURCE_FILES_SORTCACTUS})
add_executable(VCF2HMMFeature ${SOURCE_FILES_VCF2HMMFEATURE})




