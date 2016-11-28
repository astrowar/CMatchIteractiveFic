//
// Created by Eraldo Rangel on 12/10/16.
//
#include "Parser.hpp"
#include "CBlockControlFlux.hpp"
#include "sharedCast.hpp"


using namespace CBlocking;

 

HBlock NSParser::ControlFlux::stmt_resultflag(CParser *p, std::vector<HTerm>&   term)
{
	{
		static std::vector<HPred> predList = {};
		if (predList.empty()) {

			predList.push_back(mk_HPredLiteral("stop"));
			predList.push_back(mk_HPredLiteral("the"));
			predList.push_back(mk_HPredLiteral("action"));
			predList.push_back(mk_HPredLiteral("with"));
			predList.push_back(mkHPredAny("BValue"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlock BValue = Expression::parser_expression(p,res.matchs["BValue"]);
			if (BValue == nullptr) return nullptr;

			return std::make_shared<CBlockExecutionResultFlag>( PhaseResultFlag::actionStop , BValue);
		}
	}

	{
		static std::vector<HPred> predList = {};
		if (predList.empty()) 
		{
			predList.push_back(mk_HPredLiteral("stop"));
			predList.push_back(mk_HPredLiteral("the"));
			predList.push_back(mk_HPredLiteral("action"));
		}
	 
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			return std::make_shared<CBlockExecutionResultFlag>(PhaseResultFlag::actionStop, nullptr);
		}
	}

	{
		static std::vector<HPred> predList = {};
		if (predList.empty())
		{
			predList.push_back(mk_HPredLiteral("continue"));
			predList.push_back(mk_HPredLiteral("the"));
			predList.push_back(mk_HPredLiteral("action"));
		}

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			return std::make_shared<CBlockExecutionResultFlag>(PhaseResultFlag::actionContinue, nullptr);
		}
	}
	return nullptr;

}


HBlock   NSParser::ControlFlux::parser_if_condition(CParser *p, HTerm term  )
{
    {
        std::vector<HPred> predList;

        predList.push_back(mkHPredAny("AValue"));
        predList.push_back(mk_HPredLiteral("or"));
        predList.push_back(mkHPredAny("BValue"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals)
        {
            HBlock AValue = parser_if_condition(p,res.matchs["AValue"]  );
            if (AValue == nullptr) return nullptr;

            HBlock BValue = parser_if_condition(p,res.matchs["BValue"] );
            if (BValue == nullptr) return nullptr;

            return std::make_shared<CBlockBooleanOR>(AValue, BValue);
        }
    }
	 

	{
		std::vector<HPred> predList;

		predList.push_back(mkHPredAny("AValue"));
		predList.push_back(verb_IS());
		predList.push_back(mk_HPredLiteral("not"));
		predList.push_back( p->verbList);
		predList.push_back(mkHPredAny("BValue"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto vrepr = CtoString(expandBract(res.matchs[ p->verbList->named]));

			HBlock AValue = Expression::parser_expression(p,res.matchs["AValue"]);
			if (AValue == nullptr) return nullptr;

			HBlock  BValue = ExpressionMatch::parser_expression_match(p,res.matchs["BValue"]);
			if (BValue == nullptr) return nullptr;
			auto vbool = std::make_shared<CBlockIsVerb >(vrepr, AValue, BValue);
			return std::make_shared<CBlockBooleanNOT>(vbool);

		}
	}
	{
		std::vector<HPred> predList;

		predList.push_back(mkHPredAny("AValue"));
		predList.push_back(verb_IS());
		predList.push_back(p->verbList);
		predList.push_back(mkHPredAny("BValue"));

		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));

			HBlock AValue = Expression::parser_expression(p,res.matchs["AValue"]);
			if (AValue == nullptr) return nullptr;

			HBlock  BValue = ExpressionMatch::parser_expression_match(p,res.matchs["BValue"]);
			if (BValue == nullptr) return nullptr;

			return std::make_shared<CBlockIsVerb >(vrepr, AValue, BValue);
		}
	}

  

   
 {
        std::vector<HPred> predList;

        predList.push_back(mkHPredAny("AValue"));
        predList.push_back(mk_HPredLiteral("not"));
        predList.push_back(p->verbList);
        predList.push_back(mkHPredAny("BValue"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals)
        {
            auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));

            HBlock AValue = Expression::parser_expression(p,res.matchs["AValue"]);
            if (AValue == nullptr) return nullptr;

            HBlock  BValue = ExpressionMatch::parser_expression_match(p,res.matchs["BValue"]);
            if (BValue == nullptr) return nullptr;
			auto vbool = std::make_shared<CBlockIsVerb >(vrepr, AValue, BValue);
			return std::make_shared<CBlockBooleanNOT>(vbool);
       
        }
    }
    {
        std::vector<HPred> predList;

        predList.push_back(mkHPredAny("AValue"));
        predList.push_back(p->verbList);
        predList.push_back(mkHPredAny("BValue"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals)
        {
            auto vrepr = CtoString(expandBract(res.matchs[p->verbList->named]));

            HBlock AValue = Expression::parser_expression(p,res.matchs["AValue"]);
            if (AValue == nullptr) return nullptr;

            HBlock  BValue = ExpressionMatch::parser_expression_match(p,res.matchs["BValue"]);
            if (BValue == nullptr) return nullptr;

            return std::make_shared<CBlockIsVerb >(vrepr, AValue, BValue);
        }
    }


    {
        std::vector<HPred> predList;

        predList.push_back(mkHPredAny("AValue"));
        predList.push_back(mk_HPredLiteral("not"));
        predList.push_back(verb_IS());
        predList.push_back(mkHPredAny("BValue"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals)
        {
            HBlock AValue = Expression::parser_expression(p,res.matchs["AValue"]);
            if (AValue == nullptr) return nullptr;

            HBlock BValue = ExpressionMatch::parser_expression_match(p,res.matchs["BValue"]);
            if (BValue == nullptr) return nullptr;

            auto vbool =  std::make_shared<CBlockAssertion_isDirectAssign>(AValue, BValue);
			return std::make_shared<CBlockBooleanNOT>(vbool);
        }
    }



	   {
        std::vector<HPred> predList;

        predList.push_back(mkHPredAny("AValue"));
        predList.push_back(verb_IS());
        predList.push_back(mkHPredAny("BValue"));

        MatchResult res = CMatch(term, predList);
        if (res.result == Equals)
        {
            HBlock AValue = Expression::parser_expression(p,res.matchs["AValue"]);
            if (AValue == nullptr) return nullptr;

            HBlock BValue = ExpressionMatch::parser_expression_match(p,res.matchs["BValue"]);
            if (BValue == nullptr) return nullptr;

            return std::make_shared<CBlockAssertion_isDirectAssign>(AValue, BValue);
        }
    }

	 
    return Expression::parser_expression (p, term); //default ...

    return nullptr;

}

HBlock   NSParser::ControlFlux::parser_control_else(CParser *p, std::vector<HTerm>& term,   HGroupLines inner, ErrorInfo *err) {
	{
		static std::vector<HPred> predList = {};
		if (predList.empty()) 
		{
			predList.push_back(mk_HPredLiteral_OR("else", { "else" , "otherwise" }));
			predList.push_back(mk_HPredLiteral(":"));
			predList.push_back(mkHPredAny("body"));

		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals) {

			

			HBlock ABody = p->parser_stmt(res.matchs["body"], inner, err);
			if (ABody == nullptr || inner != nullptr)
			{
				err->setError("error on Select Item ");
				return nullptr;
			}
			auto token_else = std::make_shared<CBlockControlToken >("else", ABody);
			return token_else;

			// return std::make_shared<CBlockList  >( std::list<HBlock>({ token_else } )    );
		}
	}
	
	{
        static std::vector<HPred> predList = {};
        if (predList.empty()) {
			predList.push_back(mk_HPredLiteral_OR("else", { "else" , "otherwise" }));
			predList.push_back(mk_HPredLiteral(":"));
 
        }
        MatchResult res = CMatch(term, predList);
        if (res.result == Equals) {
           
			 
			HBlock executeBlock = Statement::parser_stmt_inner(p,inner, err);
			if (executeBlock == nullptr)  return nullptr;
			auto token_else = std::make_shared<CBlockControlToken >("else",executeBlock);
			return token_else;

           // return std::make_shared<CBlockList  >( std::list<HBlock>({ token_else } )    );
        }
    }
	 

    return nullptr;
}


HBlock   NSParser::ControlFlux::parser_control_end(CParser *p, std::vector<HTerm>& term, HGroupLines inner, ErrorInfo *err)
{
	//{
	//	static std::vector<HPred> predList = {};
	//	if (predList.empty()) {
	//		predList.push_back(mk_HPredLiteral("end"));

	//	}
	//	MatchResult res = CMatch(term, predList);
	//	if (res.result == Equals) {

	//		auto token_else = std::make_shared<CBlockControlToken >("end");
	//		return std::make_shared<CBlockList  >(std::list<HBlock>({ token_else }));
	//	}
	//}
	return nullptr;
}


HBlock  NSParser::ControlFlux::parser_control_if(CParser *p, std::vector<HTerm>& term, HGroupLines inner, ErrorInfo *err)
{
	if(inner == nullptr)
	{
		static std::vector<HPred> predList = {};
		if (predList.empty()) {
			predList.push_back(mk_HPredLiteral("if"));
			predList.push_back(mkHPredAny("Condition"));
			predList.push_back(mk_HPredLiteral(":"));
			predList.push_back(mkHPredAny("body"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{


			HBlock ACondition = parser_if_condition(p,res.matchs["Condition"] );

			HBlock ABody = Statement::parser_stmt(p, res.matchs["body"], nullptr, err); // aqui tem erro
			if (ABody == nullptr  )
			{
				logError(res.matchs["body"]->repr());
				err->setError("error on body   ");
				return nullptr;
			} 
			auto control_if = std::make_shared<CBlockControlIF >(ACondition, ABody, nullptr);
			return control_if;
		}

	}
	else 
    {
		static std::vector<HPred> predList = {};
		if (predList.empty()) {
			predList.push_back(mk_HPredLiteral("if"));
			predList.push_back(mkHPredAny("Condition"));
			predList.push_back(mk_HPredLiteral(":"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
        {
			HBlock ACondition = parser_if_condition(p,res.matchs["Condition"]);
			HBlock executeBlock = Statement::parser_stmt_inner(p,inner, err);
			if (executeBlock == nullptr)
			{
				err->setError("missing IF block ");
				return nullptr;
			}
			auto control_if = std::make_shared<CBlockControlIF >(ACondition, executeBlock ,nullptr);
			return control_if;
		}
	}
	return nullptr;
}
HBlock  NSParser::ControlFlux::parser_control_unless(CParser *p, std::vector<HTerm>& term, HGroupLines inner, ErrorInfo *err)
{

	{
		static std::vector<HPred> predList = {};
		if (predList.empty()) {
			predList.push_back(mk_HPredLiteral("unless"));
			predList.push_back(mkHPredAny("Condition"));
			predList.push_back(mk_HPredLiteral(":"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlock ACondition = parser_if_condition(p,res.matchs["Condition"]);
			HBlock executeBlock = Statement::parser_stmt_inner(p,inner, err);
			if (executeBlock == nullptr)
			{
				err->setError("missing Unless block ");
				return nullptr;
			}
			auto control_if = std::make_shared<CBlockControlUnless >(ACondition, executeBlock, nullptr);
			return control_if;
		}
	}
	return nullptr;
}
std::list<HBlockControlSelectItem> NSParser::ControlFlux::get_CBlockControlSelectItem(CParser *p, HBlockComandList cmdList, ErrorInfo* err)
{
	std::list<HBlockControlSelectItem> ret;
	for(auto e: cmdList->lista)
	{
		if (auto eitem = DynamicCasting::aHBlockControlSelectItem(e))
		{			
			ret.push_back(eitem);
		}
		else
		{
			err->setError("Parser Error on If Selector ");
			return std::list<HBlockControlSelectItem>();
		}
	}
	return ret;
}

HBlockControlSelect  NSParser::ControlFlux::parser_control_select(CParser *p, std::vector<HTerm>& term, HGroupLines inner, ErrorInfo *err)
{
	 


	{
		static std::vector<HPred> predList = {};
		if (predList.empty()) {
			predList.push_back(mk_HPredLiteral("if"));
			predList.push_back(mkHPredAny("object"));
			predList.push_back(mk_HPredLiteral("is"));
			predList.push_back(mk_HPredLiteral(":"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlock ACondition = Expression::parser_expression(p,res.matchs["object"] );

			HBlockComandList executeBlockRaw = Statement::parser_stmt_inner(p,inner, err);

			if (executeBlockRaw == nullptr)
			{
				err->setError("missing if block  ");
				return nullptr;
			}
			// Convert execute block to Select Item

			auto  executeBlock = get_CBlockControlSelectItem(p,  executeBlockRaw, err);
			if (err->hasError)
			{
				return nullptr;
			}

			auto control_select = std::make_shared<CBlockControlSelect >(ACondition, executeBlock, nullptr);
			return control_select;
		}
	}

	 
	return nullptr;

}



HBlockControlSelectItem  NSParser::ControlFlux::parser_control_select_item(CParser *p, std::vector<HTerm>& term, HGroupLines inner, ErrorInfo *err)
{
	{
		static std::vector<HPred> predList = {};
		if (predList.empty()) {
			predList.push_back(mk_HPredLiteral("--"));
			predList.push_back(mkHPredAny("object"));			
			predList.push_back(mk_HPredLiteral(":"));
			predList.push_back(mkHPredAny("body"));
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			
			HBlock ABody = Statement::parser_stmt ( p,  res.matchs["body"] , inner , err);
			if (ABody == nullptr || inner != nullptr)
			{
				logMessage( res.matchs["body"]->repr());				 
				err->setError("error on Select Item ");
				return nullptr;
			}
			HBlock ASeletor = Expression::parser_expression(p,res.matchs["object"]);
			return  std::make_shared<CBlockControlSelectItem  >(ASeletor, ABody );			
		}
	}

	{
		static std::vector<HPred> predList = {};
		if (predList.empty()) {
			predList.push_back(mk_HPredLiteral("--"));
			predList.push_back(mkHPredAny("object"));
			predList.push_back(mk_HPredLiteral(":"));
			 
		}
		MatchResult res = CMatch(term, predList);
		if (res.result == Equals)
		{
			HBlock ASeletor = Expression::parser_expression(p,res.matchs["object"]);
			
			HBlockComandList ABody = Statement::parser_stmt_inner(p,inner, err);
			if (ABody == nullptr)
			{
				err->setError("missing if block  ");
				return nullptr;
			}
			if (ABody == nullptr)
			{
				err->setError("error on Select Item ");
				return nullptr;
			}
			return  std::make_shared<CBlockControlSelectItem  >(ASeletor, ABody);
		}
	}


	return nullptr;

}



HBlock  NSParser::ControlFlux::STMT_control_flux(CParser *p, std::vector<HTerm>& term ,   HGroupLines inner, ErrorInfo *err)
{

//identifica os IF, then ,else, while ,case , select da vida

	HBlock rblock_flagreturn = (stmt_resultflag(p,term ));
	if (err->hasError) return nullptr;
	if (rblock_flagreturn != nullptr) return rblock_flagreturn;


	HBlock rblock_select = (parser_control_select(p,term, inner, err));
	if (err->hasError) return nullptr;
	if (rblock_select != nullptr) return rblock_select;


	HBlock rblock_select_item = (parser_control_select_item (p,term, inner, err));
	if (err->hasError) return nullptr;
	if (rblock_select_item != nullptr) return rblock_select_item;


	HBlock rblock_if = (parser_control_if(p,term, inner, err));
	if (err->hasError) return nullptr;
	if (rblock_if != nullptr) return rblock_if;
	

	 
	 
		HBlock rblock_else = (parser_control_else(p,term,  inner, err));
		if (rblock_else != nullptr) return rblock_else;
	 

	//HBlock rblock_end = (parser_control_end(term, inner, err));
    //if (rblock_end != nullptr) return rblock_end;



    return nullptr;
}

std::list<HBlock >   NSParser::ControlFlux::post_process_tokens(CParser *p,  std::list<HBlock>  lst, ErrorInfo* err)
{
	 
	// junta comandos que vem de varias linhas em um unico

	bool is_first = true;
	for(auto it = lst.begin() ; it != lst.end();++it)
	{		
		is_first = (it == lst.begin());
		{
			if (HBlockControlToken tk = DynamicCasting::aHBlockControlToken(*it))
			{
				// Entao o anterior deve ser um Comando que aceita tokens

				if (tk->token == "else")
				{  
					if (is_first )
					{
						err->setError("else without if  ");
						return std::list< HBlock  >();
					}
					auto iprev = std::prev(it);
					if (HBlockControlIF controlIF = DynamicCasting::aHBlockControlIF(*iprev))
					{
						controlIF->block_else = tk->contents;
						it = lst.erase(it);
						it = lst.begin(); // reinicia 
					}
					else if (HBlockControlSelect controlSelect = DynamicCasting::aHBlockControlSelect(*iprev))
					{
						controlSelect->block_else = tk->contents;
						it = lst.erase(it);
						it = lst.begin(); // reinicia 
					}
					else
					{
						err->setError("else without if  ");
					}
				}
			}
		}
	}


	return  lst;
}
