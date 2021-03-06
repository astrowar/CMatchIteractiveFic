// PVS
// PVQ

// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

#include "parser/Parser.hpp"
#include <array>

using namespace CBlocking;
using namespace NSTerm;
using namespace NSTerm::NSMatch;
using namespace EqualResulting;

bool is_backet_balanced(std::vector<HTerm> terms);
 
std::list<std::pair<HTerm, HTerm> > getBiPartition(std::vector<HTerm> & vs)
{
	std::list<std::pair<HTerm, HTerm> > ret;
	size_t n = vs.size();
	for (size_t halfPos = 0; halfPos < n; ++halfPos)
	{
		std::vector<HTerm> firstPart(vs.begin(), vs.begin() + halfPos);
		std::vector<HTerm> lastPart(vs.begin() + halfPos, vs.end());
		if (firstPart.empty() || lastPart.empty()) continue;
		std::pair<HTerm, HTerm> v1 = std::pair<HTerm, HTerm>(make_list(firstPart), make_list(lastPart));
		ret.push_back(v1);
	}
	return ret;

}
	 

std::list<std::pair<HTerm,HTerm> > getBiPartition(HTerm & term)
{	 
	if (CList* cs = asCList(term.get()))
	{
		
		std::vector<HTerm> vs = cs->asVector();
		return getBiPartition(vs);
		 
	}
	return	std::list<std::pair<HTerm, HTerm> >();
}


std::list<std::vector<HTerm > > getBiPartition_v(HTerm & term)
{
	if (CList* cs = asCList(term.get()))
	{

		std::vector<HTerm> vs = cs->asVector();
		std::list<std::vector<HTerm > > ret ;
		{
			auto rb = getBiPartition(vs);
			for (auto r : rb)
			{
				ret.push_back({ r.first, r.second });
			}
			return ret;
		}

	}
	return	std::list<std::vector<HTerm > >();
}




std::list<std::vector<HTerm > > getQuadPartition(std::vector<HTerm> & vs)
{
	std::list<std::vector<HTerm > > ret;
	size_t n = vs.size();

	for (size_t i1 = 1; i1 < n - 2; ++i1)
		for (size_t i2 = i1 + 1; i2 < n; ++i2)
			for (size_t i3 = i2 + 1; i3 < n; ++i3)
		{
			std::vector<HTerm> p1(vs.begin(), vs.begin() + i1);
			std::vector<HTerm> p2(vs.begin() + i1, vs.begin() + i2);
			std::vector<HTerm> p3(vs.begin() + i2, vs.begin() + i3);
			std::vector<HTerm> p4(vs.begin() + i3, vs.end());
			std::vector<HTerm > arr;
			if (p1.size() > 1) arr.push_back(make_list(p1));
			else arr.push_back(p1[0]);

			if (p2.size() > 1) arr.push_back(make_list(p2));
			else arr.push_back(p2[0]);

			if (p3.size() > 1) arr.push_back(make_list(p3));
			else arr.push_back(p3[0]);

			if (p4.size() > 1) arr.push_back(make_list(p4));
			else arr.push_back(p4[0]);
			ret.push_back(arr);
		}
	return ret;
}

std::list<std::vector<HTerm > > getQuiPartition(std::vector<HTerm> & vs)
{
	std::list<std::vector<HTerm > > ret;
	size_t n = vs.size();

	for (size_t i1 = 1; i1 < n - 2; ++i1)
	{
		std::vector<HTerm> p1(vs.begin(), vs.begin() + i1);
		HTerm item1;
		if (p1.size() > 1) item1=make_list(p1);
		else item1=p1[0];

		for (size_t i2 = i1 + 1; i2 < n; ++i2)
		{
			std::vector<HTerm> p2(vs.begin() + i1, vs.begin() + i2);
			HTerm item2;
			if (p2.size() > 1) item2 = make_list(p2);
			else item2 = p2[0];


			for (size_t i3 = i2 + 1; i3 < n; ++i3)
			{
				std::vector<HTerm> p3(vs.begin() + i2, vs.begin() + i3);
				HTerm item3;
				if (p3.size() > 1) item3 = make_list(p3);
				else item3 = p3[0];

				for (size_t i4 = i3 + 1; i4 < n; ++i4)
				{
					
					std::vector<HTerm> p4(vs.begin() + i3, vs.begin() + i4);
					std::vector<HTerm> p5(vs.begin() + i4, vs.end());

					HTerm item4;
					if (p4.size() > 1) item4 = make_list(p4);
					else item4 = p4[0];


					HTerm item5;
					if (p5.size() > 1) item5 = make_list(p5);
					else item5 = p5[0];
					 
					std::vector<HTerm > arr; 
					
					ret.push_back({item1,item2,item3,item4,item5});
				}
			}
		}
	}
	return ret;
}


 





std::list<std::vector<HTerm > > getQuiPartition(HTerm & term)
{
	if (CList* cs = asCList(term.get()))
	{
		std::list<std::vector<HTerm >> ret;
		std::vector<HTerm> vs = cs->asVector();
		if (vs.size()>4)	return getQuiPartition(vs);
	}

	return	std::list<std::vector<HTerm > >();
}

std::list<std::vector<HTerm > > getQuadPartition(HTerm & term)
{
	if (CList* cs = asCList(term.get()))
	{
		std::list<std::vector<HTerm >> ret;
		std::vector<HTerm> vs = cs->asVector();
		if (vs.size()>3) return getQuadPartition(vs);
	}

	return	std::list<std::vector<HTerm > >();
}


std::list<std::vector<HTerm > > getTriPartition(std::vector<HTerm> & vs)
{
	if (vs.front()->is_openBracket() || (vs.back()->is_closeBracket()))
	{

		if (is_backet_balanced(vs) ==false )
		{
			return std::list<std::vector<HTerm > >();
		}
	}


	std::list<std::vector<HTerm > > ret;
	size_t n = vs.size();

	for (size_t i1 = 1; i1 < n - 1; ++i1)
		for (size_t i2 = i1 + 1; i2 < n; ++i2)
		{
			std::vector<HTerm> p1(vs.begin(), vs.begin() + i1);
			std::vector<HTerm> p2(vs.begin() + i1, vs.begin() + i2);
			std::vector<HTerm> p3(vs.begin() + i2, vs.end());

			std::vector<HTerm > arr = { make_list(p1),make_list(p2),make_list(p3) };
			ret.push_back(arr);
		}
	return ret;
}

std::list<std::vector<HTerm > > getTriPartition(HTerm & term)
{
	if (CList* cs = asCList(term.get()))
	{
		std::list<std::vector<HTerm >> ret;
		std::vector<HTerm> vs = cs->asVector();
		return getTriPartition(vs); 
	}

	return	std::list<std::vector<HTerm > >();
}




std::list<std::list<HBlock > > getPartition_fn_n(int order,std::vector<HTerm>& vs, int ia, std::function<HBlock(HTerm)> func)
{

	//printf("PE %d: ",order);
	//for(auto v:vs)printf("|%s", v->repr().c_str());
	//printf("\n");

	std::list<std::list<HBlock > > ret;
	size_t n = vs.size();
	if (order == 1)
	{
		std::vector<HTerm> p1(vs.begin() + ia, vs.end());
		HTerm item1;
		if (p1.size() > 1) item1 = make_list(p1);
		else item1 = p1[0];
		HBlock ritem1 = func(item1);
		if (ritem1 == nullptr) return std::list<std::list<HBlock > >();
		
	 
		//printf("%d %x  %s \n",order, ritem1.get(), item1->repr().c_str());

		std::list<std::list<HBlock > > iret;
		iret.push_back({ ritem1 });
		return iret;
	}

	 
	

	for (size_t i1 = ia+1; i1 < n -(order) ; ++i1)
	{
		if (i1 >= n)continue;
		std::vector<HTerm> p1(vs.begin()+ia, vs.begin() + i1);
		if (p1.empty()) continue;


		//printf("H: ");
		//for (auto v : p1)printf("|%s", v->repr().c_str());
		//printf("   <=>   ");
		std::vector<HTerm> p_rem(vs.begin() + i1, vs.end());
		//for (auto v : p_rem)printf("|%s", v->repr().c_str());
		//printf("\n");

		HTerm item1;
		if (p1.size() > 1) item1 = make_list(p1);
		else item1 = p1[0];

		HBlock ritem1 = func(item1);
		if (ritem1 == nullptr)
		{
			 
			continue;

		}

		//printf("%d %x  %s \n", order, ritem1.get(), item1->repr().c_str());
		std::list<std::list<HBlock > > next_results = getPartition_fn_n(order-1,vs, i1, func); //i1 > ia
		for (auto n : next_results)
		{
			std::list<HBlock > ret_i;
			ret_i.push_back(ritem1);
			ret_i.insert(ret_i.end(), n.begin(), n.end());
			ret.push_back(ret_i);
		}		 
	}
	 

	return ret;
}

 



std::list<std::list<HBlock > > getBiPartition_fn(HTerm & term, std::function<HBlock(HTerm)> func)
{
	if (CList* cs = asCList(term.get()))
	{
		std::list<std::list<HBlock >> ret;
		std::vector<HTerm> vs = cs->asVector();
		if (vs.size() > 1)
		{
			return getPartition_fn_n(2, vs, 0, func);
		}
	}

	return	std::list<std::list<HBlock > >();
}



std::list<std::list<HBlock > > getTriPartition_fn(HTerm & term, std::function<HBlock(HTerm)> func)
{
	if (CList* cs = asCList(term.get()))
	{
		std::list<std::list<HBlock >> ret;
		std::vector<HTerm> vs = cs->asVector();
		if (vs.size() > 2)
		{
			return getPartition_fn_n(3, vs, 0, func);
		}
	}

	return	std::list<std::list<HBlock > >();
}

std::list<std::list<HBlock > > getQuadPartition_fn(HTerm & term, std::function<HBlock(HTerm)> func)
{
	if (CList* cs = asCList(term.get()))
	{
		std::list<std::list<HBlock >> ret;
		std::vector<HTerm> vs = cs->asVector();
		if (vs.size() > 3)
		{
			return getPartition_fn_n(4, vs, 0, func);
		}
	}

	return	std::list<std::list<HBlock > >();
}



std::list<std::list<HBlock > > getQuiPartition_fn(HTerm & term, std::function<HBlock(HTerm)> func)
{
	if (CList* cs = asCList(term.get()))
	{
		std::list<std::list<HBlock >> ret;
		std::vector<HTerm> vs = cs->asVector();
		if (vs.size() > 4) 
		{
			return getPartition_fn_n(5, vs, 0, func);
		}
	}

	return	std::list<std::list<HBlock > >();
}

std::list<std::list<HBlock > > getHexPartition_fn(HTerm & term, std::function<HBlock(HTerm)> func)
{
	if (CList* cs = asCList(term.get()))
	{
		std::list<std::list<HBlock >> ret;
		std::vector<HTerm> vs = cs->asVector();
		if (vs.size() > 5) 
		{
		  return 	getPartition_fn_n(6, vs, 0, func);		
		}
	}

	return	std::list<std::list<HBlock > >();
}
















HBlockMatchActionCall NSParser::ParseAction::parser_actionMatch(CParser * p, HTerm & term)
{
	
	{
		CPredSequence predList_b =  pWord("Action") << pAny("noum1") << pPreposition("pred") <<pAny("noum2");
		MatchResult res = CMatch(term, predList_b);
		if (res.result == Equals)
		{
			std::string anamed = res.matchs["Action"]->repr() + " " + res.matchs["pred"]->repr();
			HBlockMatch m_action = std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoumStr>(anamed)); 
			auto nn1 = ExpressionMatch::parser_expression_match(p, res.matchs["noum1"]);
			if (nn1 != nullptr)
			{
				auto nn2 = ExpressionMatch::parser_expression_match(p, res.matchs["noum2"]);
				if (nn2 != nullptr)
				{
					HBlockMatchActionCall actionCall = std::make_shared<CBlockMatchActionCall>(m_action, nn1, nn2); //An Action !!!
					return actionCall;
				}
			}
		}
	}


	{
		CPredSequence predList_b = pWord("Action") << pPreposition("pred") << pAny("noum1") << pLiteral("when") << pAny("Condition") ;
		MatchResult res = CMatch(term, predList_b);
		if (res.result == Equals)
		{
			std::vector<HBlockNoum> anamed = { std::make_shared<CBlockNoumStr>(res.matchs["Action"]->repr()) , std::make_shared<CBlockNoumStr>(res.matchs["pred"]->repr()) };
			HBlockMatch m_action = std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoumCompose>(anamed));
			auto nn1 = ExpressionMatch::parser_expression_match(p, res.matchs["noum1"]);
			if (nn1 != nullptr)
			{
				HBlockMatchActionCall actionCall = std::make_shared<CBlockMatchActionCall>(m_action, nn1, nullptr); //An Action !!!
				return actionCall;
			}
		}
	}





	{
		CPredSequence predList_b = pWord("Action") << pPreposition("pred") << pAny("noum1");
		MatchResult res = CMatch(term, predList_b);
		if (res.result == Equals)
		{
			std::vector<HBlockNoum> anamed = { std::make_shared<CBlockNoumStr>(res.matchs["Action"]->repr()) , std::make_shared<CBlockNoumStr>(res.matchs["pred"]->repr()) };
			HBlockMatch m_action = std::make_shared<CBlockMatchNoum>(std::make_shared<CBlockNoumCompose>(anamed));  
			auto nn1 = ExpressionMatch::parser_expression_match(p, res.matchs["noum1"]);
			if (nn1 != nullptr)
			{
					HBlockMatchActionCall actionCall = std::make_shared<CBlockMatchActionCall>(m_action, nn1, nullptr); //An Action !!!
					return actionCall;
			}
		}
	}



	 
	
	for(auto vp12 : getBiPartition(term))
	{
		//CPredSequence predList = pAny("ActionMatch")	<< pAny("Argument1");
		//MatchResult res = CMatch(term, predList);
		//if (res.result == Equals)
		{		 
			HBlockMatch m_action = ExpressionMatch::parser_expression_match(p, vp12.first );
			if (m_action != nullptr)
			{
				HBlockMatch m_arg1 = ExpressionMatch::parser_expression_match(p, vp12.second);
				if (m_arg1 != nullptr)
				{
					HBlockMatchActionCall actionCall = std::make_shared<CBlockMatchActionCall>(m_action, m_arg1, nullptr);
					return actionCall;
				}
			}
		}
	}


	{
		static CPredSequence predList = pAny("ActionMatch");
		 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlockMatch m_action = ExpressionMatch::parser_expression_match(p,res.matchs["ActionMatch"]);
			if (m_action != nullptr)
			{
				HBlockMatchActionCall actionCall = std::make_shared<CBlockMatchActionCall>(m_action, nullptr, nullptr);
				return actionCall;
			}
		}
	}



	return nullptr;
}

 
HBlock  NSParser::ParseAction::STMT_phrase_Invoken(CParser * p, std::vector<HTerm>& term)
{
	auto h = NSParser::DynamicDispatch::parser_PhraseInvoke(p, term);
	return h;
}


HBlock NSParser::ParseAction::STMT_Action_Controls(CParser * p, std::vector<HTerm>& term, HGroupLines inner, ErrorInfo *err)
{

	if (inner != nullptr)
	{
		{
			  CPredSequence predList =  pLiteral("before")	<<pAny("ActionMatch")	<<pLiteral(":");
			 
			MatchResult res = CMatch(term, predList);
			if (res.result == Equals)
			{
				HBlockMatchActionCall   amatch =  parser_actionMatch(p,res.matchs["ActionMatch"]);
				if (amatch != nullptr)
				{
				 
					HBlock executeBlock = Statement::parser_stmt_list_later(p,  inner);
					if (executeBlock != nullptr)
					{
						HBlockEventHandle actionCallEv = std::make_shared<CBlockEventHandle>(EventHandleStage::StageBefore, amatch, executeBlock);
						return actionCallEv;
					}
				}
			}
		}


		{
			  CPredSequence predList =  pLiteral("after")	<<pAny("ActionMatch")	<<pLiteral(":");
			 
			MatchResult res = CMatch(term, predList);
			if (res.result == Equals)
			{
				HBlockMatchActionCall   amatch = parser_actionMatch(p,res.matchs["ActionMatch"]);
				if (amatch != nullptr)
				{
					HBlock  executeBlock = Statement::parser_stmt_list_later(p, inner);
					if (executeBlock != nullptr)
					{
						HBlockEventHandle actionCallEv = std::make_shared<CBlockEventHandle>(EventHandleStage::StageAfter, amatch, executeBlock);
						return actionCallEv;
					}
				}
			}
		}


		{
			  CPredSequence predList =  pLiteral("check")	<<pAny("ActionMatch")	<<pLiteral(":");
		 
			MatchResult res = CMatch(term, predList);
			if (res.result == Equals)
			{
				HBlockMatchActionCall   amatch =  parser_actionMatch(p,res.matchs["ActionMatch"]);
				if (amatch != nullptr)
				{
					
					HBlock executeBlock = Statement::parser_stmt_list_later(p,  inner);
					if (executeBlock != nullptr)
					{
						HBlockEventHandle actionCallEv = std::make_shared<CBlockEventHandle>(EventHandleStage::StageCheck, amatch, executeBlock);
						return actionCallEv;
					}
				}
			}
		}


		{
			  CPredSequence predList = pLiteral("report")	<<pAny("ActionMatch")	<<pLiteral(":");
		 
			MatchResult res = CMatch(term, predList);
			if (res.result == Equals)
			{
				HBlockMatchActionCall   amatch =  parser_actionMatch(p,res.matchs["ActionMatch"]);
				if (amatch != nullptr)
				{
					HBlock executeBlock = Statement::parser_stmt_list_later(p, inner);
					if (executeBlock != nullptr)
					{
						HBlockEventHandle actionCallEv = std::make_shared<CBlockEventHandle>(EventHandleStage::StageReport, amatch, executeBlock);
						return actionCallEv;
					}
				}
			}
		}

		{
			CPredSequence predList = pLiteral("instead") << pLiteral("of") << pAny("ActionMatch") << pLiteral(":");

			MatchResult res = CMatch(term, predList);
			if (res.result == Equals)
			{
				HBlockMatchActionCall   amatch = parser_actionMatch(p, res.matchs["ActionMatch"]);
				if (amatch != nullptr)
				{
					HBlock executeBlock = Statement::parser_stmt_list_later(p, inner);
					if (executeBlock != nullptr)
					{
						HBlockEventHandle actionCallEv = std::make_shared<CBlockEventHandle>(EventHandleStage::StageInstead, amatch, executeBlock);
						return actionCallEv;
					}
				}
			}
		}


		{
			  CPredSequence predList = pLiteral("instead")	<<pAny("ActionMatch")	<<pLiteral(":");
			 
			MatchResult res = CMatch(term, predList);
			if (res.result == Equals)
			{
				HBlockMatchActionCall   amatch = parser_actionMatch(p,res.matchs["ActionMatch"]);
				if (amatch != nullptr)
				{
					HBlock  executeBlock = Statement::parser_stmt_list_later(p,inner);
					if (executeBlock != nullptr)
					{
						HBlockEventHandle actionCallEv = std::make_shared<CBlockEventHandle>(EventHandleStage::StageInstead, amatch, executeBlock);
						return actionCallEv;
					}
				}
			}
		}


		{
		 
			CPredSequence  predList = pLiteral("carry") <<  pLiteral("out") << pAny("ActionMatch")<< pLiteral(":");
		 
			MatchResult res = CMatch(term, predList);
			if (res.result == Equals)
			{
				HBlockMatchActionCall   amatch =  parser_actionMatch(p,res.matchs["ActionMatch"]);
				if (amatch != nullptr)
				{
					HBlock executeBlock = Statement::parser_stmt_list_later(p, inner);
					if (executeBlock != nullptr)
					{
						HBlockEventHandle actionCallEv = std::make_shared<CBlockEventHandle>(EventHandleStage::StageCarryOut, amatch, executeBlock);
						return actionCallEv;
					}
				}
			}
		}
	}


	return nullptr;



}
