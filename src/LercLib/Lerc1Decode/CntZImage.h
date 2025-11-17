/*
Copyright 2015 - 2022 Esri

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

A local copy of the license and additional notices are located with the
source distribution at:

http://github.com/Esri/lerc/

Contributors:  Thomas Maurer
*/

#ifndef CNTZIMAGE_H
#define CNTZIMAGE_H

#include <vector>
#include <stdexcept>
#include "TImage.hpp"

NAMESPACE_LERC_START

/**	count / z image
 *
 *	count can also be a weight, therefore float;
 *	z can be elevation or intensity;
 */

class CntZImage : public TImage< CntZ >
{
public:
  CntZImage();
  virtual ~CntZImage() {};
  std::string getTypeString() const  { return "CntZImage "; }

  /*
  warning C4263: 'LercNS::CntZImage &LercNS::CntZImage::operator =(const LercNS::CntZImage &)': member function does not override any base class virtual member function
  warning C4264: 'LercNS::TImage<LercNS::CntZ> &LercNS::TImage<LercNS::CntZ>::operator =(const LercNS::TImage<LercNS::CntZ> &)': no override available for virtual member function from base 'LercNS::TImage<LercNS::CntZ>'; function is hidden
                 see declaration of 'LercNS::TImage<LercNS::CntZ>::operator ='
                 see declaration of 'LercNS::TImage<LercNS::CntZ>'

  warning C4263: 'LercNS::CntZImage &LercNS::CntZImage::operator =(const LercNS::CntZImage &)': member function does not override any base class virtual member function
  warning C4264: 'LercNS::TImage<LercNS::CntZ> &LercNS::TImage<LercNS::CntZ>::operator =(const LercNS::TImage<LercNS::CntZ> &)': no override available for virtual member function from base 'LercNS::TImage<LercNS::CntZ>'; function is hidden
                 see declaration of 'LercNS::TImage<LercNS::CntZ>::operator ='
				 see declaration of 'LercNS::TImage<LercNS::CntZ>'
  */
  virtual TImage< CntZ >& operator=(const TImage< CntZ >& tImg) override {
	  throw std::logic_error("CntZImage: copy assignment of virtual base class not permitted.");
  }

  //virtual CntZImage& operator=(const CntZImage& tImg) = delete;
  //virtual CntZImage& operator=(const TImage<CntZ>& tImg) = delete;
  //virtual TImage<CntZ>& operator=(const TImage<CntZ>& tImg) = delete;

  bool resizeFill0(int width, int height);

  static unsigned int computeNumBytesNeededToReadHeader(bool onlyZPart);

  /// read succeeds only if maxZError on file <= maxZError requested
  bool read(const Byte** ppByte, double maxZError, bool onlyHeader = false, bool onlyZPart = false);

protected:

  struct InfoFromComputeNumBytes
  {
    double maxZError;
    bool cntsNoInt;
    int numTilesVertCnt;
    int numTilesHoriCnt;
    int numBytesCnt;
    float maxCntInImg;
    int numTilesVertZ;
    int numTilesHoriZ;
    int numBytesZ;
    float maxZInImg;
  };

  bool readTiles(bool zPart, double maxZErrorInFile, int numTilesVert, int numTilesHori, float maxValInImg, const Byte* bArr);

  bool readCntTile(const Byte** ppByte, int i0, int i1, int j0, int j1);
  bool readZTile(const Byte** ppByte, int i0, int i1, int j0, int j1, double maxZErrorInFile, float maxZInImg);

  static int numBytesFlt(float z);    // returns 1, 2, or 4
  static bool readFlt(const Byte** ppByte, float& z, int numBytes);

protected:

  InfoFromComputeNumBytes    m_infoFromComputeNumBytes;
  std::vector<unsigned int>  m_tmpDataVec;             // used in read fcts
  bool                       m_bDecoderCanIgnoreMask;  // "
};

NAMESPACE_LERC_END
#endif
