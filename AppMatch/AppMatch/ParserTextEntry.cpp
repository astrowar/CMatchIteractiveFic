

 
#include "Parser.h"

HBlock CParser::text_entry(std::vector<HTerm> term)
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
