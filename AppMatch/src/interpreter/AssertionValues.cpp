// PVS
// PVQ 

// CInform , opensource interactive fiction language
// Copyright(C) 2018  Eraldo M R Jr
// This program is free software : you can redistribute it and/or modify
// it under the terms of the Mit License
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.


//aqui
#include "sharedCast.hpp"
 
#include "sharedCast.hpp"
#include "interpreter/CBlockInterpreterRuntime.hpp"
 

using namespace std;
using namespace CBlocking;
using namespace Interpreter;
using namespace CBlocking::DynamicCasting;
 

pair<HBlockKind, HBlockKind>
CBlockInterpreter::create_derivadeKind(string called, string baseClasseName) {

    HBlockKind b = nullptr;
    HBlockKind bup = nullptr;

    if (baseClasseName == "value") {
        b = make_shared<CBlockKindValue>(called);

    } 	
	else if (baseClasseName == "entity") 
	{
        b = make_shared<CBlockKindEntity>(called);  
    } 
	else {
        // o que eh a baseclass ???
        CBlocking::HBlock r = resolve_string(baseClasseName,nullptr);

        if (HBlockKindEntity kt = asHBlockKindEntity(r)) {
            b = make_shared<CBlockKindEntity>(called);
            bup = kt;
        } else if (HBlockKindValue ktv = asHBlockKindValue(r)) {
            b = make_shared<CBlockKindValue>(called);
            bup = ktv;
        } else {
            logError("What ?? " + baseClasseName);
            return pair<HBlockKind, HBlockKind>(nullptr, nullptr);;
        }

    }
	if (existSymbol(called))
	{
		logError("Symbol alread exist \n");
		return pair<HBlockKind, HBlockKind>( nullptr,nullptr);;
	}
	addSymbol(called, b);
    return pair<HBlockKind, HBlockKind>(b, bup);

}

bool CBlockInterpreter::assert_assertation(CBlocking::HBlock obj, CBlocking::HBlock value, HRunLocalScope localsEntry)
{

	if (HBlockList_AND nobjList = asHBlockList_AND(obj))
	{
		for (auto &e : nobjList->lista)
		{
			assert_assertation(e, value, localsEntry);
		}
		return true;
	}

 
		//Static Definition de uma instancia derivado
	    if (assert_it_composition(obj, value, localsEntry)) return true;
		if (assert_it_Value(obj, value, localsEntry)) return true ;
		if (assert_it_kind(obj, value, localsEntry)) return true;
		if (assert_it_instance(obj, value, localsEntry)) return true;
		if (assert_it_valuesDefinitions(obj, value, localsEntry)) return true;
		if (assert_it_action(obj, value)) return true;

		printf("\n");
		obj->dump("");
		value->dump("");

		logError("Undefined error");
		 
		return false ;

	}


HBlockKind CBlockInterpreter::resolve_comp_kind(CBlocking::HBlockKind obj, HRunLocalScope localsEntry)
{
	if (HBlockCompositionList clist = asHBlockCompositionList(obj))
	{
		auto p = resolve_comp_kind(clist->itemKind, localsEntry);
		return std::make_shared<CBlockCompositionList>(p);
	}

	if (HBlockCompositionPhrase c = asHBlockCompositionPhrase(obj))
	{
		auto p1 = resolve_comp_kind(c->fromKind, localsEntry);
		auto p2 = resolve_comp_kind(c->toKind, localsEntry);
		return std::make_shared<CBlockCompositionPhrase>(p1,p2);
	}

	if (HBlockCompositionRelation c = asHBlockCompositionRelation(obj))
	{
		auto p1 = resolve_comp_kind(c->fromKind, localsEntry);
		auto p2 = resolve_comp_kind(c->toKind, localsEntry);
		return std::make_shared<CBlockCompositionRelation>(p1, p2);
	}

	if (HBlockKindNamed c = asHBlockKindNamed(obj))
	{
		return resolve_kind(c);
	}

	return obj;
}

bool CBlockInterpreter::assert_it_composition(CBlocking::HBlock obj, CBlocking::HBlock  value_comp, HRunLocalScope localsEntry)
{
	if (HBlockComposition c = asHBlockCompositionList(value_comp))
	{
		HBlockKind kc = resolve_comp_kind(c, localsEntry); 
		kc->dump("");
		
		if (HBlockComposition value = asHBlockCompositionList(kc))
		{

			if (HBlockCompositionList clist = asHBlockCompositionList(value))
			{
				if (HBlockNoum nobj = asHBlockNoum(obj))
				{
					HBlockList lcopy = make_shared<CBlockList>(std::list<CBlocking::HBlock>());
					return  assert_it_variableGlobal(nobj, clist, lcopy);
				}
			}

			if (HBlockCompositionPhrase cphrase = asHBlockCompositionPhrase(value))
			{

			}

			if (HBlockCompositionRelation crel = asHBlockCompositionRelation(value))
			{

			}
		}
	}
	return false;
}

bool CBlockInterpreter::assert_it_Value(CBlocking::HBlock obj, CBlocking::HBlock value, HRunLocalScope localsEntry)
{
	PhaseResult pr =  execute_set(obj, value,localsEntry);
	if (pr.hasExecuted) return  true;


 

    if (HBlockNoum nbase = asHBlockNoum(obj)) {
        CBlocking::HBlock nobj = has_resolve_noum(nbase,localsEntry);
        if (nobj != nullptr) {
            return assert_it_Value(nobj, value,localsEntry);
         
        }
     
    }

    if (HBlockInstance nInst = asHBlockInstance(obj)) {
        if (HBlockNoum nbase = asHBlockNoum(value)) {
            CBlocking::HBlock nobj = has_resolve_noum(nbase,localsEntry);
            if (nobj == nullptr) 
            {
                nInst->set(nbase);
                return true;
            }
        }
    }

 



    if (HBlockProperty prop_n = asHBlockProperty(obj)) {
        CBlocking::HBlock propNamed = prop_n->prop;
        CBlocking::HBlock destination = prop_n->obj;
        return assert_it_property(propNamed, destination, value,localsEntry,nullptr );
    }

    if (HBlockVariableNamed  var_n = asHBlockVariableNamed(obj)) {
         
        CBlocking::HBlock destination = var_n->value;
        if (value_can_be_assign_to(value , var_n->kind,localsEntry))
        {
            if (HBlockList   val_list = asHBlockList(value))
            {
                //list is passed as copy
                HBlockList lcopy = make_shared<CBlockList> (std::list<CBlocking::HBlock>());
                lcopy->lista = val_list->lista;
                var_n->value = lcopy;

            }
            else {
                var_n->value = value;
            }
            return true;
        }
        //return assert_it_property(propNamed, destination, value);
    }


    return false;

}


bool CBlockInterpreter::assert_it_action(CBlocking::HBlock obj, CBlocking::HBlock value) 
{
	 


		if (HBlockNoum nbase = asHBlockNoum(obj))
		{
			 
			 

			if (value->type() == BlockActionApply)
			{
				HBlockActionApply app = asHBlockActionApply(value);
				 
				auto ainstance = make_shared<CBlockActionInstance>(instancia_id,make_shared<CBlockKindAction>(app ));
				instancia_id++;

				this->actions_definitions.push_back(make_shared<CBlockActionNamed >(nbase->named(), make_shared<CBlockKindAction>(app)));

				addSymbol(nbase->named(), ainstance);
				return true;
			}

			//auto haction = make_shared<CBlockAction>(nbase->named);			
			//return assert_it_action(haction, value);
		}
 



    return false;
}

void CBlockInterpreter::assert_batch_kinds(std::list<CBlocking::HBlock> &nList, CBlocking::HBlockKindOfName &k)
{
	for (auto nObj : nList)
	{
		if (HBlockNoum nbasei = asHBlockNoum(nObj)) {
			auto b_up = create_derivadeKind(nbasei->named(), language->toSystemName( k->baseClasseName ));
			HBlockKind b = b_up.first;
			if (b_up.second != nullptr)
			{
				HBlockAssertion_isDirectAssign newDefi = make_shared<CBlockAssertion_isDirectAssign>(b, make_shared<CBlockKindOf>(b_up.second));                        kindDefinitions.push_back(newDefi);
				assertions.push_back(newDefi);
			}
			{
				HBlockAssertion_isDirectAssign newDefi = make_shared<CBlockAssertion_isDirectAssign>(nbasei, b);
				kindDefinitions.push_back(newDefi);
				assertions.push_back(newDefi);
			}
			logMessage("new Kind add");
		}
	}
}

bool CBlockInterpreter::assert_it_kind(CBlocking::HBlock obj, CBlocking::HBlock value, HRunLocalScope localsEntry) {
	if (HBlockKindOfName k = asHBlockKindOfName(value)) 
	{

		if (HBlockNoumStrDet ndet = asHBlockNoumStrDet(obj))
		{
			return assert_it_kind(ndet->noum, value, localsEntry);
		}

		if (HBlockNoum nbase = asHBlockNoum(obj)) 
		{

			auto b_up = create_derivadeKind(language->toSystemName(nbase), language->toSystemName( k->baseClasseName));
			HBlockKind b = b_up.first;

			if (b_up.second != nullptr) {

				HBlockAssertion_isDirectAssign newDefi = make_shared<CBlockAssertion_isDirectAssign>(b,
					make_shared<CBlockKindOf>(
						b_up.second));
				kindDefinitions.push_back(newDefi);
				assertions.push_back(newDefi);
			}

			{

				HBlockAssertion_isDirectAssign newDefi = make_shared<CBlockAssertion_isDirectAssign>(nbase, b);
				kindDefinitions.push_back(newDefi);
				assertions.push_back(newDefi);
			}

			if (symbols.exist(this->language, nbase) == false)
			{
				symbols.add(nbase->named(), b);
				logMessage("new Kind add " + nbase->named());
			}

			return true;
		}

		//Processa a lista
		else if (HBlockList nList = asHBlockList(obj))
		{
			assert_batch_kinds(nList->lista, k);
			return true;
		}
		else if (HBlockList nList = asHBlockList(obj))
		{
			assert_batch_kinds(nList->lista, k);
			return true;
		}
	}
	return false;

}



bool CBlockInterpreter::assert_it_instance(CBlocking::HBlock obj, CBlocking::HBlock baseKind, HRunLocalScope localsEntry) {

    if (HBlockList baseList = asHBlockList(baseKind))
    {

		//bool p1 = assert_it_instance(obj, baseList->lista.back(), localsEntry);

		for (auto ee = baseList->lista.rbegin(); ee != baseList->lista.rend(); ++ee)
		{
			assert_assertation(obj, *ee, localsEntry);
		}
        
        return true;
    }

	if (HBlockList nobjList = asHBlockList(obj))
	{

		for (auto &e : nobjList->lista)
		{
			assert_it_instance(e, baseKind, localsEntry);
		}
		return true;
	}



	if (HBlockList_AND nobjList = asHBlockList_AND(obj))
	{
		for (auto &e : nobjList->lista) 
		{
			assert_it_instance(e, baseKind, localsEntry);
		}
		return true;
	}

    if (HBlockNoum nbaseKind = asHBlockNoum(baseKind))
    {
        CBlocking::HBlock bbase = resolve_noum(nbaseKind, localsEntry);
        if (bbase != nullptr)
        {
            return assert_it_instance(obj, bbase, localsEntry);
        }


		std::pair<HBlockNoum, CBlocking::HBlockKind>  descritive_kind = resolve_descritive_kind(nbaseKind, localsEntry);
		if (descritive_kind.second != nullptr)
		{
			 bool p1 =  assert_it_instance(obj, descritive_kind.second, localsEntry);
			 if (p1)
			 {
				 return assert_it_Value(obj, descritive_kind.first, localsEntry); 
			 }
			 else
			 {
				  
				 return false;
			 }
		}
        else
        {
            logError("Kind not found " + nbaseKind->named());
            return false;
        }
    }

     
 
        if (HBlockNoum nobj = asHBlockNoum(obj)) 
        {
           
            if (HBlockKind k = asHBlockKind(baseKind)) 
            {
                //HBlockInstance binstance = make_shared<CBlockInstance>(nobj->named);

                HBlockInstance binstance = new_Instance(nobj->named(), k);

                HBlockAssertion_isDirectAssign newDefi = make_shared<CBlockAssertion_isDirectAssign>(obj, binstance);
                HBlockAssertion_isInstanceOf newInst = make_shared<CBlockAssertion_isInstanceOf>(binstance, k);
                assertions.push_back(newDefi);
                assertions.push_back(newInst);
                instancias.push_back(binstance);
                logMessage("new Instance add " + (nobj->named())    );

				addSymbol(nobj->named(), binstance);

                return true;
            }
           
        }

          
        

    

    return false;
}

bool CBlockInterpreter::assert_it_valuesDefinitions_list(CBlocking::HBlock c_block, std::list< CBlocking::HBlock> values, HRunLocalScope localsEntry) 
{
	 
		if (HBlockNoum nn = asHBlockNoum(c_block)) //primeiro eh um noum
		{
			// nn eh um value Kind ??
			CBlocking::HBlock nobj = resolve_noum(nn, localsEntry);
			if (nobj != nullptr)
			{
				return assert_it_valuesDefinitions_list(nobj, values, localsEntry);
			}

			//nn is plural of anything ?
			HBlockNoum singular_form = get_singular_of(nn->named());
			if (singular_form != nullptr)
			{
				return assert_it_valuesDefinitions_list(singular_form, values, localsEntry);
			}

		}

		{
			if (HBlockKind nkind = asHBlockKind(c_block)) //mas na verdade o primeiro eh um kind ja definido
			{
				for (auto &v : values)
				{
					assert_it_instance(v, nkind, localsEntry);
				}
				return true;
			}
		}


	return false;

}

bool CBlockInterpreter::assert_it_valuesDefinitions(CBlocking::HBlock c_block, CBlocking::HBlock value, HRunLocalScope localsEntry) {
    // Value Kind , is , list of Noums

	if (HBlockList vlist = asHBlockList(value)) // segundo argumento eh uma lista
	{
		return assert_it_valuesDefinitions_list(c_block, vlist->lista, localsEntry);
	}
	if (HBlockList_AND vlist = asHBlockList_AND(value)) // segundo argumento eh uma lista
	{
		return assert_it_valuesDefinitions_list(c_block, vlist->lista, localsEntry);
	}
         
	return false;
}

bool CBlockInterpreter::assert_newUnderstand(HBlockUnderstandDynamic value)
{
    dynamic_understand.push_back(value);
    return true;
}
