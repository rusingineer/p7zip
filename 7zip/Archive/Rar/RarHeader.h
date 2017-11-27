// Archive::Rar::Header.h

// #pragma once

#ifndef __ARCHIVE_RAR_HEADER_H
#define __ARCHIVE_RAR_HEADER_H

#include "Common/Types.h"

#pragma pack(push, PragmaRarHeaders)
#pragma pack(push, 1)

#ifdef __GNUC__   // FIXME - FIXED for gcc 2.95
#define PACKED __attribute__((packed))
#else
#define PACKED
#endif

namespace NArchive{
namespace NRar{
namespace NHeader{

const int kMarkerSize = 7;
extern BYTE kMarker[kMarkerSize];
  
const int kArchiveSolid = 0x1;

namespace NBlockType
{
  enum EBlockType
  { 
    kMarker        = 0x72,
    kArchiveHeader = 0x73,
    kFileHeader    = 0x74,
    kCommentHeader = 0x75,
    kOldAuthenticity = 0x76,
    kSubBlock       = 0x77,
    kRecoveryRecord = 0x78,
    kAuthenticity   = 0x79,

    kEndOfArchive   = 0x7B // Is not safe
  };
}

namespace NArchive
{
  const UINT16 kVolume  = 1;
  const UINT16 kComment = 2;
  const UINT16 kLock    = 4;
  const UINT16 kSolid   = 8;
  const UINT16 kNewVolName = 0x10; // ('volname.partN.rar')
  const UINT16 kAuthenticity  = 0x20;
  const UINT16 kRecovery = 0x40;
  const UINT16 kBlockEncryption  = 0x80;
  const UINT16 kFirstVolume = 0x100; // (set only by RAR 3.0 and later)
  
  struct CBlock
  {
    UINT16 CRC PACKED ;
    BYTE Type PACKED ;
    UINT16 Flags PACKED ;
    UINT16 Size PACKED ;
    UINT16 Reserved1 PACKED ;
    UINT32 Reserved2 PACKED ;
    UINT16 GetRealCRC() const;
  };

  const int kBlockHeadersAreEncrypted = 0x80;
}

namespace NFile
{
  const int kSplitBefore = 1 << 0;
  const int kSplitAfter  = 1 << 1;
  const int kEncrypted   = 1 << 2;
  const int kComment     = 1 << 3;
  const int kSolid       = 1 << 4;
  
  const int kDictBitStart     = 5;
  const int kNumDictBits  = 3;
  const int kDictMask         = (1 << kNumDictBits) - 1;
  const int kDictDirectoryValue  = 0x7;
  
  const int kSize64Bits    = 1 << 8;
  const int kUnicodeName   = 1 << 9;
  const int kSalt          = 1 << 10;
  const int kOldVersion    = 1 << 11;
  const int kExtTime       = 1 << 12;
  // const int kExtFlags      = 1 << 13;
  // const int kSkipIfUnknown = 1 << 14;

  const int kLongBlock    = 1 << 15;
  
  struct CBlock
  {
    // UINT16 HeadCRC;
    // BYTE Type;
    // UINT16 Flags;
    // UINT16 HeadSize;
    UINT32 PackSize PACKED ;
    UINT32 UnPackSize PACKED ;
    BYTE HostOS PACKED ;
    UINT32 FileCRC PACKED ;
    UINT32 Time PACKED ;
    BYTE UnPackVersion PACKED ;
    BYTE Method PACKED ;
    UINT16 NameSize PACKED ;
    UINT32 Attributes PACKED ;
  };

    /*
  struct CBlock32
  {
    UINT16 HeadCRC;
    BYTE Type;
    UINT16 Flags;
    UINT16 HeadSize;
    UINT32 PackSize;
    UINT32 UnPackSize;
    BYTE HostOS;
    UINT32 FileCRC;
    UINT32 Time;
    BYTE UnPackVersion;
    BYTE Method;
    UINT16 NameSize;
    UINT32 Attributes;
    UINT16 GetRealCRC(const void *aName, UINT32 aNameSize, 
        bool anExtraDataDefined = false, BYTE *anExtraData = 0) const;
  };
  struct CBlock64
  {
    UINT16 HeadCRC;
    BYTE Type;
    UINT16 Flags;
    UINT16 HeadSize;
    UINT32 PackSizeLow;
    UINT32 UnPackSizeLow;
    BYTE HostOS;
    UINT32 FileCRC;
    UINT32 Time;
    BYTE UnPackVersion;
    BYTE Method;
    UINT16 NameSize;
    UINT32 Attributes;
    UINT32 PackSizeHigh;
    UINT32 UnPackSizeHigh;
    UINT16 GetRealCRC(const void *aName, UINT32 aNameSize) const;
  };
  */
  
  const int kLabelFileAttribute            = 0x08;
  const int kWinFileDirectoryAttributeMask = 0x10;
  
  enum CHostOS
  { 
    kHostMSDOS = 0, 
      kHostOS2   = 1, 
      kHostWin32 = 2, 
      kHostUnix  = 3,
      kHostMacOS = 4,
      kHostBeOS = 5
  };
}

namespace NBlock
{
  const UINT16 kLongBlock = 1 << 15;
  struct CBlock
  {
    UINT16 CRC PACKED ;
    BYTE Type PACKED ;
    UINT16 Flags PACKED ;
    UINT16 HeadSize PACKED ;
    //  UINT32 DataSize;
  };
}

struct CSubBlock
{
  UINT16 HeadCRC PACKED ;
  BYTE HeadType PACKED ;
  UINT16 Flags PACKED ;
  UINT16 HeadSize PACKED ;
  UINT32 DataSize PACKED ;
  UINT16 SubType PACKED ;
  BYTE Level PACKED ; // Reserved : Must be 0
};

struct CCommentBlock
{
  UINT16 HeadCRC PACKED ;
  BYTE HeadType PACKED ;
  UINT16 Flags PACKED ;
  UINT16 HeadSize PACKED ;
  UINT16 UnpSize PACKED ;
  BYTE UnpVer PACKED ;
  BYTE Method PACKED ;
  UINT16 CommCRC PACKED ;
};


struct CProtectHeader
{
  UINT16 HeadCRC PACKED ;
  BYTE HeadType PACKED ;
  UINT16 Flags PACKED ;
  UINT16 HeadSize PACKED ;
  UINT32 DataSize PACKED ;
  BYTE Version PACKED ;
  UINT16 RecSectors PACKED ;
  UINT32 TotalBlocks PACKED ;
  BYTE Mark[8] PACKED ;
};

}}}

#pragma pack(pop)
#pragma pack(pop, PragmaRarHeaders)

#endif
