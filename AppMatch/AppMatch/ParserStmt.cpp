#include "Parser.hpp"
using namespace CBlocking;


HBlock NSParser::Expression::parser_kind(CParser *p, HTerm term)
{

	return Expression::parser_expression(p,term);
}
HBlock NSParser::Expression::parser_kind_or_instance(CParser *p, HTerm term) { return Expression::parser_expression(p,term); }
HBlock NSParser::Expression::parser_valueReference(CParser *p, HTerm term) { return Expression::parser_expression(p,term); }
HBlock NSParser::Expression::parser_assertionTarger(CParser *p, HTerm term)
{
	HBlock pdet = ParseSelector::parser_List_selector(p,term);
	if (pdet != nullptr) return pdet;
	return Expression::parser_expression(p,term);
}
 


 
 

HBlock   NSParser::ParseAssertion::parser_VerbAssign(CParser * p, std::vector<HTerm>& term)
{

	HBlock aVerb = parse_AssertionVerb(p,term);
	if (aVerb != nullptr)
	{
		return aVerb;
	}

	HBlock aDirect = parse_AssertionDirectAssign(p,term);
	if (aDirect != nullptr)
	{
		return aDirect;
	}

	return nullptr;
}


HBlock NSParser::Expression::parser_expression(CParser *p, HTerm  term)
{
	if (CList *vlist = asCList(term.get())) {
		auto rvector = vlist->asVector();
		auto r = parser_expression_lst(p,rvector);
		/*if (r == nullptr)
		std::cout << term->repr() << std::endl;*/
		return r;
	}
	//return std::make_shared<CBlockNoum>(term->removeArticle()->repr());
	//std::cout << term->repr() << std::endl; 
	return std::make_shared<CBlockNoum>(CtoString( term->removeArticle()) );
}

HBlock  NSParser::Expression::parser_expression_lst(CParser *p, std::vector<HTerm>&   lst)
{

	HBlock rblock_textEntry = (Statement::text_entry(p,lst));
	if (rblock_textEntry != nullptr) return rblock_textEntry;



	 
	 

	HBlock adapt_verb = ParseGrammar::expression_adapt_verb(p,lst);
	if (adapt_verb != nullptr) {
		return adapt_verb;
	}

	HBlock rblock_dynamicEntry_1 = (DynamicDispatch::DynamicDispatch_action(p,lst));
	if (rblock_dynamicEntry_1 != nullptr) return rblock_dynamicEntry_1;

	 


	HBlock rblock_Lookup = (ParseRelation::DynamicLookup_Seletor(p,lst));
	if (rblock_Lookup != nullptr) return rblock_Lookup;


	 

	HBlock rblock_assert_1 = (ParseAssertion::parser_VerbAssign(p,lst));
	if (rblock_assert_1 != nullptr) return rblock_assert_1;


	HBlock noumListAND_Assign = ParseList::parse_List_AND(p,lst);
    if (noumListAND_Assign != nullptr) {
        return noumListAND_Assign;
    }

	HBlock noumListOR_Assign = ParseList::parse_List_OR(p,lst);
	if (noumListOR_Assign != nullptr) {
		return noumListOR_Assign;
	}

    HBlock detnoum_Assign = ParseAssertion::parse_removeArticle(p,lst);
    if (detnoum_Assign != nullptr) {
        return detnoum_Assign;
    }

	HBlock noum_propOF = ParseAssertion::parse_PropertyOf(p,lst);
	if (noum_propOF != nullptr) {
		return noum_propOF;
	}

	 
	 



    HBlock noum_Assign = ParseAssertion::parse_noum(p,lst);
    if (noum_Assign != nullptr) {
        return noum_Assign;
    }

	return nullptr;
}
HBlock NSParser::Statement::parser_stmt_inner(CParser * p, std::vector<HTerm>& lst, HGroupLines inner, ErrorInfo *err)
{
 

	HBlock rblock_system_control = (ControlFlux::STMT_control_flux(p,lst,inner , err));
	if (rblock_system_control != nullptr) return rblock_system_control;
 
	if (err->hasError) return nullptr;
	//Apenas os termos que iniciam uma sentenca completa

	HBlock rblock_tryEntry_1 = (DynamicDispatch::TryDispatch_action(p,lst));
	if (rblock_tryEntry_1 != nullptr) return rblock_tryEntry_1;

   /* HBlock rblock_decide_blc = (parser_decides_Assertion(lst));
    if (rblock_decide_blc != nullptr) return rblock_decide_blc;*/

	HBlock rblock_system_stmt = (ParseAssertion::STMT_system_Assertion(p,lst  ));
	if (rblock_system_stmt != nullptr) return rblock_system_stmt;

    HBlock rblock_understand_1 = (ParseAssertion::STMT_understand_Assertion(p,lst  ));
    if (rblock_understand_1 != nullptr) return rblock_understand_1;

	HBlock rblock_action_controls = (ParseAction::STMT_Action_Controls(p,lst, inner, err));
	if (rblock_action_controls != nullptr) return rblock_action_controls;



	HBlock rblock_relatesTo = (ParseRelation::STMT_relates_Assertion(p,lst ));
	if (rblock_relatesTo != nullptr) return rblock_relatesTo;

	HBlock rblock_decide_1 = (ParseAssertion::STMT_Decide_Assertion(p,lst, inner, err));
	if (rblock_decide_1 != nullptr) return rblock_decide_1;

    HBlock rblock_verb_1n = (Verbal::STMT_verb_Assertion_N(p,lst ));
    if (rblock_verb_1n != nullptr) return rblock_verb_1n;

    HBlock rblock_verb_1 = (Verbal::STMT_verb_Assertion(p,lst ));
    if (rblock_verb_1 != nullptr) return rblock_verb_1;

    HBlock rblock_definition_1 = (ParseDecide::STMT_Definition_Assertion(p,lst)); //To define ...
    if (rblock_definition_1 != nullptr) return rblock_definition_1;

   // HBlock rblock_decide_1 = (STMT_Decide_Assertion(lst,inner, err));
   // if (rblock_decide_1 != nullptr) return rblock_decide_1;
  

    HBlock rblock_assert_1 = (ParseAssertion::parser_Declaration_Assertion(p,lst));
    if (rblock_assert_1 != nullptr) return rblock_assert_1;

    HBlock rblock_assert_hasA = (ParseAssertion::STMT_hasAn_Assertion(p,lst));
    if (rblock_assert_hasA != nullptr) return rblock_assert_hasA;

    HBlock rblock_assert_2 = (ParseAssertion::STMT_canBe_Assertion(p,lst));
    if (rblock_assert_2 != nullptr) return rblock_assert_2;

	HBlock rblock_register_verb = (ParseGrammar::STMT_register_verb(p,lst, inner, err));
	if (rblock_register_verb != nullptr) return rblock_register_verb;
    
	logError(get_repr(lst));

    return nullptr;

}
