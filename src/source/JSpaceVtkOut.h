//HEAD_DSCODES
/*
 <DUALSPHYSICS>  Copyright (c) 2019 by Dr Jose M. Dominguez et al. (see http://dual.sphysics.org/index.php/developers/). 

 EPHYSLAB Environmental Physics Laboratory, Universidade de Vigo, Ourense, Spain.
 School of Mechanical, Aerospace and Civil Engineering, University of Manchester, Manchester, U.K.

 This file is part of DualSPHysics. 

 DualSPHysics is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License 
 as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.
 
 DualSPHysics is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details. 

 You should have received a copy of the GNU Lesser General Public License along with DualSPHysics. If not, see <http://www.gnu.org/licenses/>. 
*/

//:#############################################################################
//:# Cambios:
//:# =========
//:# - Gestiona lista de archivos VTK con geometria generados por GenCase. (30-07-2018)
//:# - Nuevo metodo para obtener la lista de ficheros con una clave. (06-08-2018)
//:# - Nuevo metodo para obtener el fichero segun su posicion. (01-05-2019)
//:#############################################################################

/// \file JSpaceVtkOut.h \brief Declares the class \ref JSpaceVtkOut.

#ifndef _JSpaceVtkOut_
#define _JSpaceVtkOut_

#include "JObject.h"
#include "TypesDef.h"
#include <vector>

class JXml;
class TiXmlElement;

//##############################################################################
//# JSpaceVtkOutFile
//##############################################################################
/// \brief Manages the information of one VTK file.

class JSpaceVtkOutFile
{
protected:
  std::string ListMk;
public:
  const std::string File;

  JSpaceVtkOutFile(const std::string &file,const std::string &mks);
  ~JSpaceVtkOutFile();
  void Reset();

  void SetMks(const std::string &mks);
  std::string GetMks()const{ return(ListMk); }
};


//##############################################################################
//# JSpaceVtkOut
//##############################################################################
/// \brief Manages the information of output VTK files generated by GenCase.

class JSpaceVtkOut : protected JObject
{
private:
  word MkBoundFirst;
  word MkFluidFirst;

  std::vector<JSpaceVtkOutFile*> Files;

  void ReadXml(const JXml *sxml,TiXmlElement* lis);
  void WriteXml(JXml *sxml,TiXmlElement* lis)const;

public:
  JSpaceVtkOut();
  ~JSpaceVtkOut();
  void Reset();

  void ConfigMkFirst(word mkboundfirst,word mkfluidfirst);
  void AddFile(const std::string &fname,const std::string &mks);

  unsigned Count()const{ return(unsigned(Files.size())); }
  unsigned GetByFileName(std::string fname)const;

  std::string GetFile(unsigned idx)const;
  void GetFiles(std::string key,std::vector<std::string> &list)const;

  std::string GetListMkType(bool bound,const std::string &mks)const;

  void LoadXml(const JXml *sxml,const std::string &place,bool optional);
  void SaveXml(JXml *sxml,const std::string &place)const;
};

#endif

