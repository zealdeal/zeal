// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "txdb.h"
#include "main.h"
#include "uint256.h"


static const int nCheckpointSpan = 500;

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (  0,     uint256("0x0000066e91e46e5a264d42c89e1204963b2ee6be230b443e9159020539d972af") )
        (  2,     uint256("0xbca5936f638181e74a5f1e9999c95b0ce77da48c2688399e72bcc53a00c61eff") ) // Premine
        ( 50,     uint256("0x0353b43f4ce80bf24578e7c0141d90d7962fb3a4b4b4e5a17925ca95e943b816") )
        ( 100,    uint256("0x688468a8aa48cd1c2197e42e7d8acd42760b7e2ac4bcab9d18ac149a673e16f6") )
        ( 150,    uint256("0xe4ae9663519abec15e28f68bdb2cb89a739aee22f53d1573048d69141db6ee5d") )
        ( 127500, uint256("0x4773ca7512489df22de03aa03938412fab5b46154b05df004b97bcbeaa184078") )
        ( 128943, uint256("0x36bcaa27a53d3adf22b2064150a297adb02ac39c24263a5ceb73856832d49679") ) 
        ( 136601, uint256("0xf5c5210c55ff1ef9c04715420a82728e1647f3473e31dc478b3745a97b4a6d10") ) // Hardfork to v2.0.0
        ( 170000, uint256("0x22b10952e0cf7e85bfc81c38f1490708f195bff34d2951d193cc20e9ca1fc9d5") )
        ( 200000, uint256("0x2391dd493be5d0ff0ef57c3b08c73eefeecc2701b80f983054bb262f7a146989") )
        ( 250000, uint256("0x681c70fab7c1527246138f0cf937f0eb013838b929fbe9a831af02a60fc4bf55") )
        ( 300000, uint256("0xd10ca8c2f065a49ae566c7c9d7a2030f4b8b7f71e4c6fc6b2a02509f94cdcd44") )
        ( 350000, uint256("0xe2b76d1a068c4342f91db7b89b66e0f2146d3a4706c21f3a262737bb7339253a") )
        ( 390000, uint256("0x4682737abc2a3257fdf4c3c119deb09cbac75981969e2ffa998b4f76b7c657bb") )
        ( 394000, uint256("0x42857fa2bc15d45cdcaae83411f755b95985da1cb464ee23f6d40936df523e9f") )
        ( 400000, uint256("0x4938d5cf450b4e2d9072558971223555055aa3987b634a8bb2e97f95d1a3c501") )
        ( 450000, uint256("0x7699e07ac18c25ac042deb6b985e2decfd6034cb6361de2152a2d704ef785bac") )
        ( 500000, uint256("0x558700d99239e64017d10910466719fe1edc6f863bd3de254b89ba828818ea47") )
        ( 550000, uint256("0x83d074957f509772b1fbbfaeb7bdc52932c540d54e205b92a7d4e92f68957eb4") )
        ( 600000, uint256("0xcd05c75c0c47060d78508095c0766452f80e2defb6a4641ac603742a2ccf2207") )
        ( 650000, uint256("0xa2814a439b33662f43bdbc8ab089d368524975bb53a08326395e57456cba8d39") )
        ( 700000, uint256("0x782b2506bb67bb448ff56aa946f7aad6b63a6b27d8c5818725a56b568f25b9ce") )
        ( 750000, uint256("0x4db98bd41a2f9ee845cc89ac03109686f615f4d0dcd81e0488005c1616fa692c") )
        ( 800000, uint256("0x161da1d97d35d6897dbdae110617bb839805f8b02d33ac23d227a87cacbfac78") )
        ( 850000, uint256("0xc3a249b01795b22858aa00fd0973471fcd769a14f4f9cf0abe6651ac3e6ade19") )
    ;

    // TestNet has no checkpoints
    static MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        ( 0,      uint256("0x00000e246d7b73b88c9ab55f2e5e94d9e22d471def3df5ea448f5576b1d156b9") )
        ( 2,      uint256("0x56959b1c8498631fb0ca5fe7bd83319dccdc6ac003dccb3171f39f553ecfa2f2") ) // Premine
        ( 50000,  uint256("0xb42c18eacf8fb5ed94eac31943bd364451d88da0fd44cc49616ffea34d530ad4") )
        ( 100000, uint256("0xf9e2f7561ee4b92d3bde400d251363a0e8924204c326da7f4ad9ccc8863aad79") )
        ( 150000, uint256("0x08b7c20a450252ddf9ce41dbeb92ecf54932beac9090dc8250e933ad3a175381") )
        ( 200000, uint256("0x8609cc873222a0573615788dc32e377b88bfd6a0015791f627d969ee3a415115") )
        ( 250000, uint256("0xdd664e15ac679a6f3b96a7176303956661998174a697ad8231f154f1e32ff4a3") )
        ( 300000, uint256("0x2409eb5ae72c80d5b37c77903d75a8e742a33843ab633935ce6e5264db962e23") )
        ( 350000, uint256("0x36811041e9060f4b4c26dc20e0850dca5efaabb60618e3456992e9c0b1b2120e") )
        ( 400000, uint256("0xb6abcb933d3e3590345ca5d3abb697461093313f8886568ac8ae740d223e56f6") )
    ;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        if (checkpoints.empty())
            return 0;
        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    // Automatically select a suitable sync-checkpoint 
    const CBlockIndex* AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Check against synchronized checkpoint
    bool CheckSync(int nHeight)
    {
        const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();

        if (nHeight <= pindexSync->nHeight)
            return false;
        return true;
    }
}
