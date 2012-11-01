//
//  FileLocationUtility.cpp
//  PhysicsSynth
//
//  Created by Jonathan Hook on 31/10/2012.
//  Copyright (c) 2012 Jonathan Hook. All rights reserved.
//
#include "FileLocationUtility.h"

namespace JDHUtility
{
    std::string FileLocationUtility::resourcePath = "";
    
    const std::string FileLocationUtility::getFileInResourcePath(const std::string &path)
    {
        std::string p = resourcePath;
        p.append("/");
        p.append(path);
        return p;
    }
    
    void FileLocationUtility::setResourcePath(const std::string &path)
    {
        resourcePath = path;
    }
}