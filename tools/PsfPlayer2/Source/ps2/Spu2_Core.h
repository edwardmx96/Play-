#ifndef _SPU2_CORE_H_
#define _SPU2_CORE_H_

#include <string>
#include <functional>
#include <boost/utility.hpp>
#include "Types.h"
#include "../BasicUnions.h"
#include "Spu2_Channel.h"

namespace PS2
{
	namespace Spu2
	{
		class CCore : public boost::noncopyable
		{
		public:
							CCore(unsigned int);
			virtual			~CCore();

			void			Reset();

			uint32			ReadRegister(uint32, uint32);
			uint32			WriteRegister(uint32, uint32);
            uint32          ReceiveDma(uint8*, uint32, uint32);

			enum REGISTERS
			{
				VP_VOLL			= 0x1F900000,
				VP_VOLR			= 0x1F900002,
				VP_PITCH		= 0x1F900004,
				VP_ADSR1		= 0x1F900006,
				VP_ADSR2		= 0x1F900008,
				VP_ENVX			= 0x1F90000A,
				VP_VOLXL		= 0x1F90000C,
				VP_VOLXR		= 0x1F90000E,
				S_REG_BASE		= 0x1F900180,
				A_TSA_HI		= 0x1F9001A8,
				A_TSA_LO		= 0x1F9001AA,
				A_STD			= 0x1F9001AC,
				VA_REG_BASE		= 0x1F9001C0,
				VA_SSA_HI		= 0x1F9001C0,
				VA_SSA_LO		= 0x1F9001C2,
				VA_LSAX			= 0x1F9001C4,
				VA_NAX			= 0x1F9001C8,
				R_REG_BASE		= 0x1F9002E0,		//Reverb Base
				STATX			= 0x1F900344,
			};

		private:
			typedef uint32 (CCore::*RegisterAccessFunction)(unsigned int, uint32, uint32);

			enum
			{
				MAX_CHANNEL = 24,
			};

	        enum
	        {
		        RAMSIZE = 0x80000
	        };

			struct REGISTER_DISPATCH_INFO
			{
				RegisterAccessFunction	core;
				RegisterAccessFunction	channel;
			};

			uint32					ProcessRegisterAccess(const REGISTER_DISPATCH_INFO&, uint32, uint32);

			uint32					ReadRegisterCore(unsigned int, uint32, uint32);
			uint32					WriteRegisterCore(unsigned int, uint32, uint32);

			uint32					ReadRegisterChannel(unsigned int, uint32, uint32);
			uint32					WriteRegisterChannel(unsigned int, uint32, uint32);

			void					LogRead(uint32);
			void					LogWrite(uint32, uint32);
			void					LogChannelRead(unsigned int, uint32);
			void					LogChannelWrite(unsigned int, uint32, uint32);

			REGISTER_DISPATCH_INFO	m_readDispatch;
			REGISTER_DISPATCH_INFO	m_writeDispatch;
            uint8*                  m_ram;
			CChannel				m_channel[MAX_CHANNEL];
			unsigned int			m_coreId;
			UNION32_16				m_transferAddress;
			std::string				m_logName;
		};
	};
};

#endif