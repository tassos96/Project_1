#include "CmdArgumentsReader.h"

using namespace std;

LshCmdVariables* setLshArguments(int argc, char const *argv[])
{
    LshCmdVariables* lshCmdVariables = new LshCmdVariables;
    for(int i = 1; i < argc; i += 2)
    {
        if (strcmp(argv[i],"-d") == 0 || strcmp(argv[i], "-D") == 0)
        {
            lshCmdVariables->inputFileName = argv[i+1];
        }
        else if(strcmp(argv[i],"-q") == 0 || strcmp(argv[i], "-Q") == 0)
        {
            lshCmdVariables->queryFileName = argv[i+1];
        }
        else if(strcmp(argv[i],"-k") == 0 || strcmp(argv[i], "-K") == 0)
        {
            lshCmdVariables->K = stoi(argv[i+1]);
        }
        else if(strcmp(argv[i],"-l") == 0 || strcmp(argv[i], "-L") == 0)
        {
            lshCmdVariables->L = stoi(argv[i+1]);
        }
        else if(strcmp(argv[i],"-o") == 0 || strcmp(argv[i], "-O") == 0)
        {
            lshCmdVariables->outputFileName = argv[i+1];
        }
        else if(strcmp(argv[i],"-n") == 0 || strcmp(argv[i], "-N") == 0)
        {
            lshCmdVariables->N = stoi(argv[i+1]);
        }
        else if(strcmp(argv[i],"-r") == 0 || strcmp(argv[i], "-R") == 0)
        {
            lshCmdVariables->R = stof(argv[i+1]);
        }
    }
    return lshCmdVariables;
}

CubeCmdVariables* setCubeArguments(int argc, char const *argv[])
{
    CubeCmdVariables* cubeCmdVariables = new CubeCmdVariables;
    for(int i = 1; i < argc; i += 2)
    {
        if (strcmp(argv[i],"-d") == 0 || strcmp(argv[i], "-D") == 0)
        {
            cubeCmdVariables->inputFileName = argv[i+1];
        }
        else if(strcmp(argv[i],"-q") == 0 || strcmp(argv[i], "-Q") == 0)
        {
            cubeCmdVariables->queryFileName = argv[i+1];
        }
        else if(strcmp(argv[i],"-k") == 0 || strcmp(argv[i], "-K") == 0)
        {
            cubeCmdVariables->K = stoi(argv[i+1]);
        }
        else if(strcmp(argv[i],"-m") == 0 || strcmp(argv[i], "-M") == 0)
        {
            cubeCmdVariables->M = stoi(argv[i+1]);
        }
        else if(strcmp(argv[i],"-probes") == 0 || strcmp(argv[i], "-PROBES") == 0)
        {
            cubeCmdVariables->probes = stoi(argv[i+1]);
        }
        else if(strcmp(argv[i],"-o") == 0 || strcmp(argv[i], "-O") == 0)
        {
            cubeCmdVariables->outputFileName = argv[i+1];
        }
        else if(strcmp(argv[i],"-n") == 0 || strcmp(argv[i], "-N") == 0)
        {
            cubeCmdVariables->N = stoi(argv[i+1]);
        }
        else if(strcmp(argv[i],"-r") == 0 || strcmp(argv[i], "-R") == 0)
        {
            cubeCmdVariables->R = stof(argv[i+1]);
        }
    }
    return cubeCmdVariables;
}

ClusterCmdVariables* setClusterArguments(int argc, char const *argv[])
{
    ClusterCmdVariables* clusterCmdVariables = new ClusterCmdVariables;
    for(int i = 1; i < argc; i += 2)
    {
        if (strcmp(argv[i],"-i") == 0 || strcmp(argv[i], "-I") == 0)
        {
            clusterCmdVariables->inputFileName = argv[i+1];
        }
        else if(strcmp(argv[i],"-c") == 0 || strcmp(argv[i], "-C") == 0)
        {
            clusterCmdVariables->configFileName = argv[i+1];
        }
        else if(strcmp(argv[i],"-o") == 0 || strcmp(argv[i], "-O") == 0)
        {
            clusterCmdVariables->outputFileName = argv[i+1];
        }
        else if(strcmp(argv[i],"-optional") == 0 || strcmp(argv[i], "-OPTIONAL") == 0)
        {
            clusterCmdVariables->optional = argv[i+1];
        }
        else if(strcmp(argv[i],"-m") == 0 || strcmp(argv[i], "-M") == 0)
        {
            clusterCmdVariables->method = argv[i+1];
        }
    }
    return clusterCmdVariables;
}

