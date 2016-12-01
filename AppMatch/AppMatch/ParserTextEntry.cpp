// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

 
#include "Parser.hpp"
using namespace CBlocking;
using namespace NSTerm;
using namespace NSTerm::NSMatch;




HBlock NSParser::Statement::text_entry(CParser * p, std::vector<HTerm>&  term)
{
	{
		 
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mk_HPredLiteral("text"));
			predList.push_back(mkHPredAny("Contents"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) 
		{
			string  ss = CtoString(res.matchs["Contents"]);
			return  std::make_shared<CBlockText >( ss );
			
		}
	}
	

	return nullptr;
}
