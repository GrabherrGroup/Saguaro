cmake_minimum_required(VERSION 3.3)
project(saguaro)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread -std=c++14 -O3 -w")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

# Saguaro binaries
set(SOURCE_FILES_CACTICORRELATE ryggrad/base/CommandLineParser.h ryggrad/base/ErrorHandling.h ryggrad/base/FileParser.h ryggrad/base/SVector.h ryggrad/base/StringUtil.h ryggrad/math/Spearman.h src/CactiCorrelate.cc ryggrad/util/mutil.h) 
set(SOURCE_FILES_CHROMOPAINTCACTI ryggrad/base/CommandLineParser.h ryggrad/base/ErrorHandling.h ryggrad/base/FileParser.h ryggrad/base/SVector.h ryggrad/base/StringUtil.h src/ChromoPaintCacti.cc src/DNAVector.h ryggrad/util/mutil.h ryggrad/visual/Axes.h ryggrad/visual/Color.h ryggrad/visual/Eps.h ryggrad/visual/TicMarks.h ryggrad/visual/Whiteboard.h) 
set(SOURCE_FILES_CLUSTERCACTI ryggrad/base/CommandLineParser.h ryggrad/base/ErrorHandling.h ryggrad/base/FileParser.h ryggrad/base/SVector.h ryggrad/base/StringUtil.h src/Cactus.h src/ClusterCacti.cc ryggrad/util/mutil.h) 
set(SOURCE_FILES_FASTA2HMMFEATURE ryggrad/base/CommandLineParser.h ryggrad/base/ErrorHandling.h ryggrad/base/FileParser.h ryggrad/base/SVector.h ryggrad/base/StringUtil.h src/DNAVector.h src/Fasta2HMMFeature.cc src/HMMDistance.h ryggrad/util/mutil.h) 
set(SOURCE_FILES_FILTERCACTI ryggrad/base/CommandLineParser.h ryggrad/base/ErrorHandling.h ryggrad/base/FileParser.h ryggrad/base/SVector.h ryggrad/base/StringUtil.h src/Cactus.h src/FilterCacti.cc ryggrad/util/mutil.h) 
set(SOURCE_FILES_FILTERFEATURES ryggrad/base/CommandLineParser.h ryggrad/base/ErrorHandling.h ryggrad/base/FileParser.h ryggrad/base/SVector.h ryggrad/base/StringUtil.h src/DNAVector.h src/FilterFeatures.cc src/HMMDistance.h ryggrad/util/mutil.h) 
set(SOURCE_FILES_FREQ2HMMFEATURE ryggrad/base/CommandLineParser.h ryggrad/base/ErrorHandling.h ryggrad/base/FileParser.h ryggrad/base/SVector.h ryggrad/base/StringUtil.h src/DNAVector.h src/Freq2HMMFeature.cc src/HMMDistance.h ryggrad/util/mutil.h) 
set(SOURCE_FILES_GENOTYPE2HMMFEATURE ryggrad/base/CommandLineParser.h ryggrad/base/ErrorHandling.h ryggrad/base/FileParser.h ryggrad/base/SVector.h ryggrad/base/StringUtil.h src/DNAVector.h src/Genotype2HMMFeature.cc src/HMMDistance.h ryggrad/util/mutil.h)
set(SOURCE_FILES_HMMCLASSIFY  ryggrad/base/CommandLineParser.h ryggrad/base/ErrorHandling.h ryggrad/base/FileParser.h ryggrad/base/SVector.h ryggrad/base/StringUtil.h src/HMMClassify.cc src/HMMDecode.h ryggrad/util/mutil.h) 
set(SOURCE_FILES_HMMTRAIN ryggrad/base/CommandLineParser.h ryggrad/base/ErrorHandling.h ryggrad/base/FileParser.h ryggrad/base/RandomStuff.h ryggrad/base/SVector.h ryggrad/base/StringUtil.h src/HMMDecode.h src/HMMDistance.h src/HMMTrain.cc src/SOM.h ryggrad/util/mutil.h) 
set(SOURCE_FILES_LOCALTREES ryggrad/base/CommandLineParser.h ryggrad/base/ErrorHandling.h ryggrad/base/FileParser.h ryggrad/base/RandomStuff.h ryggrad/base/SVector.h ryggrad/base/StringUtil.h src/HMMDecode.h src/HMMDistance.h src/LocalTrees.cc src/SOM.h ryggrad/util/mutil.h) 
set(SOURCE_FILES_MAF2HMMFEATURE ryggrad/base/CommandLineParser.h ryggrad/base/ErrorHandling.h ryggrad/base/FileParser.h ryggrad/base/SVector.h ryggrad/base/StringUtil.h src/DNAVector.h src/HMMDistance.h src/Maf2HMMFeature.cc ryggrad/util/mutil.h) 
set(SOURCE_FILES_PULLFROMFASTA ryggrad/base/CommandLineParser.h ryggrad/base/ErrorHandling.h ryggrad/base/FileParser.h ryggrad/base/SVector.h ryggrad/base/StringUtil.h src/DNAVector.h src/PullFromFasta.cc ryggrad/util/mutil.h) 
set(SOURCE_FILES_SAGUARO ryggrad/base/CommandLineParser.h ryggrad/base/ErrorHandling.h ryggrad/base/FileParser.h ryggrad/base/SVector.h ryggrad/base/StringUtil.h src/HMMDecode.h src/HMMDistance.h src/Saguaro.cc ryggrad/util/mutil.h) 
set(SOURCE_FILES_SAGUARO2PHYLIP ryggrad/base/CommandLineParser.h ryggrad/base/ErrorHandling.h ryggrad/base/FileParser.h ryggrad/base/SVector.h ryggrad/base/StringUtil.h src/Saguaro2Phylip.cc ryggrad/util/mutil.h) 
set(SOURCE_FILES_SORTCACTUS ryggrad/base/CommandLineParser.h ryggrad/base/ErrorHandling.h ryggrad/base/FileParser.h ryggrad/base/SVector.h ryggrad/base/StringUtil.h src/SortCactus.cc ryggrad/util/mutil.h) 
set(SOURCE_FILES_VCF2HMMFEATURE ryggrad/base/CommandLineParser.h ryggrad/base/ErrorHandling.h ryggrad/base/FileParser.h ryggrad/base/SVector.h ryggrad/base/StringUtil.h src/DNAVector.h src/HMMDistance.h src/VCF2HMMFeature.cc ryggrad/util/mutil.h) 

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




