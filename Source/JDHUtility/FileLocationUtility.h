//
//  FileLocationUtility.h
//  PhysicsSynth
//
//  Created by Jonathan Hook on 31/10/2012.
//  Copyright (c) 2012 Jonathan Hook. All rights reserved.
//
#include <string>

namespace JDHUtility
{
	class FileLocationUtility
	{
    public:
        static const std::string    getFileInResourcePath   (const std::string &path);
        static void                 setResourcePath         (const std::string &path);
        
    private:
        static std::string resourcePath;
    };
}
