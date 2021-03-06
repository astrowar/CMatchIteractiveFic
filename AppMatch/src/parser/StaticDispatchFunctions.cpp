// PVS
// PVQ


// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.


#include "parser/Parser.hpp"
 
#include <algorithm>


#include "CBlockMatch.hpp"
#include "CBlockBoolean.hpp"
#include "CblockAssertion.hpp"
 
using namespace CBlocking;
using namespace NSTerm;
using namespace NSTerm::NSMatch;



 


HBlockNoum NSParser::CParser::get_next_headerName()
{
	this->phase_id++;
	return std::make_shared<CBlockNoumStr>("Phase"+std::to_string(this->phase_id));
}

NSParser::staticDispatchEntry::staticDispatchEntry(HBlockMatchList _argumentsMatch, HBlock _action) : entryArguments(
        _argumentsMatch), action(_action) {

}

NSParser::staticDispatchEntry::staticDispatchEntry() : entryArguments(nullptr), action(nullptr) {

}

 

NSParser::SentenceDispatchPredicate::SentenceDispatchPredicate(std::vector<HPred> _matchPhase, HBlockMatch _matchPhaseDynamic,
	HBlock _output, int _entryId) : matchPhase(_matchPhase),
	_matchPhaseDynamic(_matchPhaseDynamic),
	output(_output),
	entryId(_entryId) {

}

int NSParser::CParser::registerStaticDispatch(int entry, HBlockMatchList argumentMatch, HBlock body) {
    for (auto it = staticDispatch.begin(); it != staticDispatch.end(); ++it) {
        if (it->entryId == entry) {
            staticDispatchEntry sEntry(argumentMatch, body);
            it->entries.push_back(sEntry);
            return entry;
        }
    }
    //nao achei nenhum que ja existe

    StaticDispatchArgument sdisp(entry);
    sdisp.entries.push_back(staticDispatchEntry(argumentMatch, body));
    staticDispatch.push_back(sdisp);
    return entry;
}


int NSParser::CParser::registerDynamicDispatch(std::vector<HPred> _matchPhase, HBlockMatch entry) {

    //Verifica se ja tem a sentenceDispatch
    int maxID = 0;
    for (auto it = sentenceDispatch.begin(); it != sentenceDispatch.end(); ++it) {
        maxID = std::max(maxID, it->entryId);
        if (isSamePred(it->matchPhase, _matchPhase)) {
            return it->entryId;
        }
    }

    //nao tem nenhum ... Cria um novo
    SentenceDispatchPredicate sdisp(_matchPhase, entry, nullptr, maxID + 1);
    sentenceDispatch.push_back(sdisp);

    sentenceDispatch.sort([](const SentenceDispatchPredicate &a, const SentenceDispatchPredicate &b) -> bool {
        return a.matchPhase.size() > b.matchPhase.size();
    });

   logMessage( "Dynamic Registed " );
    entry->dump("    ");

    return maxID + 1;
}

int NSParser::CParser::registerDynamicDispatch(std::vector<HPred> _matchPhase, HBlockMatch entry , HBlock ret) {

	//Verifica se ja tem a sentenceDispatch
	int maxID = 0;
	for (auto it = sentenceDispatch.begin(); it != sentenceDispatch.end(); ++it) {
		maxID = std::max(maxID, it->entryId);
		if (isSamePred(it->matchPhase, _matchPhase)) {
			return it->entryId;
		}
	}

	//nao tem nenhum ... Cria um novo
	SentenceDispatchPredicate sdisp(_matchPhase, entry, ret, maxID + 1);
	sentenceDispatch.push_back(sdisp);

	sentenceDispatch.sort([](const SentenceDispatchPredicate &a, const SentenceDispatchPredicate &b) -> bool {
		return a.matchPhase.size() > b.matchPhase.size();
	});

	logMessage("Dynamic Registed ");
	entry->dump("    ");

	return maxID + 1;
}