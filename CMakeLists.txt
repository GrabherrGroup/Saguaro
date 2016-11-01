cmake_minimum_required(VERSION 3.3)
project(saguaro)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++14 -O3 -w")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)

# include directory in find path where all dependency modules exist
include_directories(./)


# saguaro binaries
set(SOURCE_FILES_CACTICORRELATE ryggrad/src/base/ErrorHandling.cc ryggrad/src/base/FileParser.cc ryggrad/src/base/StringUtil.cc src/CactiCorrelate.cc ryggrad/src/util/mutil.cc) 
set(SOURCE_FILES_CHROMOPAINTCACTI ryggrad/src/base/ErrorHandling.cc ryggrad/src/base/FileParser.cc ryggrad/src/base/StringUtil.cc src/ChromoPaintCacti.cc ryggrad/src/general/DNAVector.cc ryggrad/src/util/mutil.cc ryggrad/src/visual/Color.cc ryggrad/src/visual/Eps.cc) 
set(SOURCE_FILES_CLUSTERCACTI ryggrad/src/base/ErrorHandling.cc ryggrad/src/base/FileParser.cc ryggrad/src/base/StringUtil.cc src/Cactus.cc src/ClusterCacti.cc ryggrad/src/util/mutil.cc) 
set(SOURCE_FILES_FASTA2HMMFEATURE ryggrad/src/base/ErrorHandling.cc ryggrad/src/base/FileParser.cc ryggrad/src/base/StringUtil.cc ryggrad/src/general/DNAVector.cc src/Fasta2HMMFeature.cc src/HMMDistance.cc ryggrad/src/util/mutil.cc) 
set(SOURCE_FILES_FILTERCACTI ryggrad/src/base/ErrorHandling.cc ryggrad/src/base/FileParser.cc ryggrad/src/base/StringUtil.cc src/Cactus.cc src/FilterCacti.cc ryggrad/src/util/mutil.cc) 
set(SOURCE_FILES_FILTERFEATURES ryggrad/src/base/ErrorHandling.cc ryggrad/src/base/FileParser.cc ryggrad/src/base/StringUtil.cc ryggrad/src/general/DNAVector.cc src/FilterFeatures.cc src/HMMDistance.cc ryggrad/src/util/mutil.cc) 
set(SOURCE_FILES_FREQ2HMMFEATURE ryggrad/src/base/ErrorHandling.cc ryggrad/src/base/FileParser.cc ryggrad/src/base/StringUtil.cc ryggrad/src/general/DNAVector.cc src/Freq2HMMFeature.cc src/HMMDistance.cc ryggrad/src/util/mutil.cc) 
set(SOURCE_FILES_GENOTYPE2HMMFEATURE ryggrad/src/base/ErrorHandling.cc ryggrad/src/base/FileParser.cc ryggrad/src/base/StringUtil.cc ryggrad/src/general/DNAVector.cc src/Genotype2HMMFeature.cc src/HMMDistance.cc ryggrad/src/util/mutil.cc)
set(SOURCE_FILES_HMMCLASSIFY  ryggrad/src/base/ErrorHandling.cc ryggrad/src/base/FileParser.cc ryggrad/src/base/StringUtil.cc src/HMMClassify.cc src/HMMDecode.cc ryggrad/src/util/mutil.cc) 
set(SOURCE_FILES_HMMTRAIN ryggrad/src/base/ErrorHandling.cc ryggrad/src/base/FileParser.cc ryggrad/src/general/DNAVector.cc ryggrad/src/base/StringUtil.cc src/HMMDecode.cc src/HMMDistance.cc src/HMMTrain.cc src/SOM.cc ryggrad/src/util/mutil.cc) 
set(SOURCE_FILES_LOCALTREES ryggrad/src/base/ErrorHandling.cc ryggrad/src/base/FileParser.cc ryggrad/src/general/DNAVector.cc ryggrad/src/base/StringUtil.cc src/HMMDecode.cc src/HMMDistance.cc src/LocalTrees.cc src/SOM.cc ryggrad/src/util/mutil.cc) 
set(SOURCE_FILES_MAF2HMMFEATURE ryggrad/src/base/ErrorHandling.cc ryggrad/src/base/FileParser.cc ryggrad/src/base/StringUtil.cc ryggrad/src/general/DNAVector.cc src/HMMDistance.cc src/Maf2HMMFeature.cc ryggrad/src/util/mutil.cc) 
set(SOURCE_FILES_PULLFROMFASTA ryggrad/src/base/ErrorHandling.cc ryggrad/src/base/FileParser.cc ryggrad/src/base/StringUtil.cc ryggrad/src/general/DNAVector.cc src/PullFromFasta.cc ryggrad/src/util/mutil.cc) 
set(SOURCE_FILES_SAGUARO ryggrad/src/base/ErrorHandling.cc ryggrad/src/base/FileParser.cc ryggrad/src/base/StringUtil.cc ryggrad/src/general/DNAVector.cc src/HMMDecode.cc src/HMMDistance.cc src/Saguaro.cc ryggrad/src/util/mutil.cc) 
set(SOURCE_FILES_SAGUARO2PHYLIP ryggrad/src/base/ErrorHandling.cc ryggrad/src/base/FileParser.cc ryggrad/src/base/StringUtil.cc src/Saguaro2Phylip.cc ryggrad/src/util/mutil.cc) 
set(SOURCE_FILES_SORTCACTUS ryggrad/src/base/ErrorHandling.cc ryggrad/src/base/FileParser.cc ryggrad/src/base/StringUtil.cc src/SortCactus.cc ryggrad/src/util/mutil.cc) 
set(SOURCE_FILES_VCF2HMMFEATURE ryggrad/src/base/ErrorHandling.cc ryggrad/src/base/FileParser.cc ryggrad/src/base/StringUtil.cc ryggrad/src/general/DNAVector.cc src/HMMDistance.cc src/VCF2HMMFeature.cc ryggrad/src/util/mutil.cc) 

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




