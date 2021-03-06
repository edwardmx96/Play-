#ifndef _IOP_LOADCORE_H_
#define _IOP_LOADCORE_H_

#include "Iop_Module.h"
#include "Iop_SifMan.h"
#include <functional>

class CIopBios;

namespace Iop
{
	class CLoadcore : public CModule, public CSifModule
	{
	public:
		enum MODULE_ID
		{
			MODULE_ID = 0x80000006
		};

		typedef std::function<uint32 (const char*, const char*)> LoadExecutableHandler;

									CLoadcore(CIopBios&, uint8*, CSifMan&);
		virtual						~CLoadcore();

		std::string					GetId() const;
		std::string					GetFunctionName(unsigned int) const;
		void						Invoke(CMIPS&, unsigned int);
		bool						Invoke(uint32, uint32*, uint32, uint32*, uint32, uint8*);

		void						SetLoadExecutableHandler(const LoadExecutableHandler&);

	private:
		uint32						RegisterLibraryEntries(uint32);
		uint32						QueryBootMode(uint32);
		uint32						SetRebootTimeLibraryHandlingMode(uint32, uint32);

		bool						LoadModule(uint32*, uint32, uint32*, uint32);
		void						LoadExecutable(uint32*, uint32, uint32*, uint32);
		void						LoadModuleFromMemory(uint32*, uint32, uint32*, uint32);
		void						SearchModuleByName(uint32*, uint32, uint32*, uint32);
		void						Initialize(uint32*, uint32, uint32*, uint32);

		CIopBios&					m_bios;
		uint8*						m_ram;

		LoadExecutableHandler		m_loadExecutableHandler;
	};
}

#endif
