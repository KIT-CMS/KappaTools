/* Copyright (c) 2010 - All Rights Reserved
 *   Andreas Oehler <andreasoehler@gmx.net>
 *   Armin Burgmeier <burgmeier@ekp.uni-karlsruhe.de>
 *   Fred Stober <stober@cern.ch>
 *   Manuel Zeise <zeise@cern.ch>
 */

#ifndef KAPPA_FILEINTERFACE_H
#define KAPPA_FILEINTERFACE_H

#include "../../Toolbox/interface/ProgressMonitor.h"
#include "../../Toolbox/interface/IOHelper.h"
#include "FileInterfaceBase.h"

class FileInterface : public FileInterfaceBase
{
public:
	FileInterface(std::vector<std::string> files, bool shuffle = false, int verbose = 2);
	~FileInterface()
	{
		ClearCache();
	}
	using FileInterfaceBase::Get;

	// Functions for getting metadata objects
	template<typename T>
	T *Get(run_id run, lumi_id lumi);
	template<typename T>
	inline T *Get(KEventInfo *info_event);

	// Get lumi list
	std::vector<std::pair<run_id, lumi_id> > GetRunLumis() const;
	bool isCompatible(unsigned int minRun, unsigned int maxRun);

	TChain eventdata;
private:
	TChain lumidata;
	TChain rundata;
	int verbosity;

	std::map<std::pair<run_id, lumi_id>, KGenRunInfo> lumimap_mc;
	std::map<std::pair<run_id, lumi_id>, KLumiInfo> lumimap_std;
	std::map<std::pair<run_id, lumi_id>, KDataLumiInfo> lumimap_data;

	template<typename T>
	std::map<std::pair<run_id, lumi_id>, T> GetLumis();
};

#include "FileInterface.hxx"

#endif
