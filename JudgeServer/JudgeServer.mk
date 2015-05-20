##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=JudgeServer
ConfigurationName      :=Debug
WorkspacePath          := "/home/micky/Documents/Coding/SimpleAlgorithmJudge/JudgeServer"
ProjectPath            := "/home/micky/Documents/Coding/SimpleAlgorithmJudge/JudgeServer"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=micky
Date                   :=20/05/15
CodeLitePath           :="/home/micky/.codelite"
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="JudgeServer.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/BasicSocket.cc$(ObjectSuffix) $(IntermediateDirectory)/main.cc$(ObjectSuffix) $(IntermediateDirectory)/PollManager.cc$(ObjectSuffix) $(IntermediateDirectory)/ServerSocket.cc$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/BasicSocket.cc$(ObjectSuffix): BasicSocket.cc $(IntermediateDirectory)/BasicSocket.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/micky/Documents/Coding/SimpleAlgorithmJudge/JudgeServer/BasicSocket.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/BasicSocket.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/BasicSocket.cc$(DependSuffix): BasicSocket.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/BasicSocket.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/BasicSocket.cc$(DependSuffix) -MM "BasicSocket.cc"

$(IntermediateDirectory)/BasicSocket.cc$(PreprocessSuffix): BasicSocket.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/BasicSocket.cc$(PreprocessSuffix) "BasicSocket.cc"

$(IntermediateDirectory)/main.cc$(ObjectSuffix): main.cc $(IntermediateDirectory)/main.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/micky/Documents/Coding/SimpleAlgorithmJudge/JudgeServer/main.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cc$(DependSuffix): main.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cc$(DependSuffix) -MM "main.cc"

$(IntermediateDirectory)/main.cc$(PreprocessSuffix): main.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cc$(PreprocessSuffix) "main.cc"

$(IntermediateDirectory)/PollManager.cc$(ObjectSuffix): PollManager.cc $(IntermediateDirectory)/PollManager.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/micky/Documents/Coding/SimpleAlgorithmJudge/JudgeServer/PollManager.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PollManager.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PollManager.cc$(DependSuffix): PollManager.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PollManager.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/PollManager.cc$(DependSuffix) -MM "PollManager.cc"

$(IntermediateDirectory)/PollManager.cc$(PreprocessSuffix): PollManager.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PollManager.cc$(PreprocessSuffix) "PollManager.cc"

$(IntermediateDirectory)/ServerSocket.cc$(ObjectSuffix): ServerSocket.cc $(IntermediateDirectory)/ServerSocket.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/micky/Documents/Coding/SimpleAlgorithmJudge/JudgeServer/ServerSocket.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ServerSocket.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ServerSocket.cc$(DependSuffix): ServerSocket.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ServerSocket.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/ServerSocket.cc$(DependSuffix) -MM "ServerSocket.cc"

$(IntermediateDirectory)/ServerSocket.cc$(PreprocessSuffix): ServerSocket.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ServerSocket.cc$(PreprocessSuffix) "ServerSocket.cc"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


