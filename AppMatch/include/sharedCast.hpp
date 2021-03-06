#ifndef SharedCast_HPP
#define SharedCast_HPP

#include "BlockInterpreter.hpp"
#include "CBlockAction.hpp"
#include "CBlockUndestand.hpp"
#include "CBlockDecideIf.hpp"
#include "CBlockRelation.hpp"
#include "BlockInstance.hpp"
#include "CBlockDumpValues.hpp"
#include "CBlockCommand.hpp"
#include "CBlockBoolean.hpp"
#include "CBlockControlFlux.hpp" 
#include "CBlockNumber.hpp"
#include "CBlockComposition.hpp"
#include "CBlockCompostion.hpp"
#include "CBlockScope.hpp"
#include "CblockAssertion.hpp"

//#include "interpreter/CBlockInterpreterRuntime.hpp"

namespace CBlocking
{
	namespace DynamicCasting
	{


		//invalidos	
		//Interpreter::HBlockInterpreter asHBlockInterpreter(CBlocking::HBlock  c);
		HBlockBooleanResult    asHBlockBooleanResult(CBlocking::HBlock  c);
		HBlockFilter    asHBlockFilter(CBlocking::HBlock  c);
		HBlockUnderstand asHBlockUnderstand(CBlocking::HBlock  c);
		HBlockCompostionPhrase asHBlockCompostionPhrase(CBlocking::HBlock  c);
		HBlockIF  asHBlockIF(CBlocking::HBlock  c);
		HBlockFilterList asHBlockFilterList(CBlocking::HBlock  c);
		HBlockExecution asHBlockExecution(CBlocking::HBlock  c);
		HBlockFilterAtom asHBlockFilterAtom(CBlocking::HBlock  c);
		HBlockMatchWith asHBlockMatchWith(CBlocking::HBlock  c);
		HBlockSame asHBlockSame(CBlocking::HBlock  c);




		HBlockEnums asHBlockEnums(CBlocking::HBlock c);
		HBlockKind asHBlockKind(CBlocking::HBlock c);
		HUnresolved asHUnresolved(CBlocking::HBlock c);
		HBlockKindOf asHBlockKindOf(CBlocking::HBlock c);
		HBlockKindAction asHBlockKindAction(CBlocking::HBlock c);
		HBlockKindValue asHBlockKindValue(CBlocking::HBlock c);
	 
		HBlockNamedValue asHBlockNamedValue(CBlocking::HBlock c);
 
		HBlockAssertion_isLocalVariable asHBlockAssertion_isLocalVariable(CBlocking::HBlock c);
		HBlockInstanceVariable asHBlockInstanceVariable(CBlocking::HBlock c);
		HBlockCollection asHBlockCollection(CBlocking::HBlock c);
		HBlockList asHBlockList(CBlocking::HBlock c);
		HBlockList_AND asHBlockList_AND(CBlocking::HBlock c);
		HBlockList_OR asHBlockList_OR(CBlocking::HBlock c);
		HBlockEnums asHBlockEnums(CBlocking::HBlock c);
		HBlockProperty asHBlockProperty(CBlocking::HBlock c);
		HBlockAssertion_isDefaultAssign asHBlockAssertion_isDefaultAssign(CBlocking::HBlock c);
		HBlockNothing asHBlockNothing(CBlocking::HBlock c);
		HBlockComposition asHBlockComposition(CBlocking::HBlock c);
		HBlockCompositionList asHBlockCompositionList(CBlocking::HBlock c);
		HBlockCompositionPhrase asHBlockCompositionPhrase(CBlocking::HBlock c);
		HBlockCompositionRelation asHBlockCompositionRelation(CBlocking::HBlock c);

		HBlockNoum asHBlockNoum(CBlocking::HBlock c);

		HBlockNoumSupl asHBlockNoumSupl(CBlocking::HBlock c);

		HBlockKindNamed  asHBlockKindNamed(CBlocking::HBlock c);
		HBlockKind_InstanceVariable asHBlockKind_InstanceVariable(CBlocking::HBlock c);
		HBlockAssertion_isDirectAssign asHBlockAssertion_isDirectAssign(CBlocking::HBlock c);
		HBlockAssertion_canBe asHBlockAssertion_canBe(CBlocking::HBlock c);
		HBlockAssertion_is asHBlockAssertion_is(CBlocking::HBlock c);
		HBlockIsVerb asHBlockIsVerb(CBlocking::HBlock c);
		//HBlockAssertion_isActionOf asHBlockAssertion_isActionOf(CBlocking::HBlock c);
		HBlockMatchIsVerbComposition    asHBlockMatchIsVerbComposition(CBlocking::HBlock  c);
		HBlockIsNotVerb asHBlockIsNotVerb(CBlocking::HBlock c);
		HBlockMatchAny asHBlockMatchAny(CBlocking::HBlock c);
		HBlockMatchText asHBlockMatchText(CBlocking::HBlock c);		 

		HBlockMatchNoum asHBlockMatchNoum(CBlocking::HBlock c);
		HBlockMatchNamed asHBlockMatchNamed(CBlocking::HBlock c);
		HBlockMatchList asHBlockMatchList(CBlocking::HBlock c);
		HBlockMatchDirectIsNot asHBlockMatchDirectIsNot(CBlocking::HBlock c);
		HBlockMatchKind asHBlockMatchKind(CBlocking::HBlock c);
		HBlockMatchValue asHBlockMatchValue(CBlocking::HBlock c);
		HBlockMatchProperty asHBlockMatchProperty(CBlocking::HBlock c);
		HBlockMatchBlock asHBlockMatchBlock(CBlocking::HBlock c);
		HBlockMatchOR asHBlockMatchOR(CBlocking::HBlock c);
		HBlockMatchAND asHBlockMatchAND(CBlocking::HBlock c);
		HBlockMatchNOT asHBlockMatchNOT(CBlocking::HBlock c);
		HBlockMatchDirectIs asHBlockMatchDirectIs(CBlocking::HBlock c);
		HBlockMatchWhich asHBlockMatchWhich(CBlocking::HBlock c);
		HBlockMatchWhichNot asHBlockMatchWhichNot(CBlocking::HBlock c);
		HBlockMatchIsVerb asHBlockMatchIsVerb(CBlocking::HBlock c);
		HBlockMatchIsNotVerb asHBlockMatchIsNotVerb(CBlocking::HBlock c);
		HBlockMatchNoum asHBlockMatchNoum(CBlocking::HBlock c);

		HBlockMatch asHBlockMatch(CBlocking::HBlock c);


		HBlockAssertion_isNotDirectAssign asHBlockAssertion_isNotDirectAssign(CBlocking::HBlock c);

		HBlockBooleanAND asHBlockBooleanAND(CBlocking::HBlock c);

 
		HBlockPhraseInvoke asHBlockPhraseInvoke(CBlocking::HBlock c);
		HBlockPhraseHeader asHBlockPhraseHeader(CBlocking::HBlock c);		 
		HBlockPhraseDefine asHBlockPhraseDefine(CBlocking::HBlock c);

		HBlockIsAdverbialComparasion asHBlockIsAdverbialComparasion(CBlocking::HBlock c);
		HBlockMatchIsAdverbialComparasion asHBlockMatchIsAdverbialComparasion(CBlocking::HBlock c);

		HBlockVerb asHBlockVerb(CBlocking::HBlock c);
		HBlockVerbAdapt asHBlockVerbAdapt(CBlocking::HBlock c);
		HBlockVerbNegate asHBlockVerbNegate(CBlocking::HBlock c);
		HBlockEventHandle asHBlockEventHandle(CBlocking::HBlock c);
		HBlockBooleanOR asHBlockBooleanOR(CBlocking::HBlock c);
		HBlockBooleanNOT asHBlockBooleanNOT(CBlocking::HBlock c);
		HBlockSelector_All asHBlockSelector_All(CBlocking::HBlock c);
		HBlockSelector_Any asHBlockSelector_Any(CBlocking::HBlock c);
		HBlockStaticDispatch asHBlockStaticDispatch(CBlocking::HBlock c);
		HBlockActionInstance asHBlockActionInstance(CBlocking::HBlock c);
		HBlockAction asHBlockAction(CBlocking::HBlock c);
		HBlockActionNamed asHBlockActionNamed(CBlocking::HBlock c);
		
		HBlockTryCall asHBlockTryCall(CBlocking::HBlock c);
		HBlockActionCall asHBlockActionCall(CBlocking::HBlock c);

		HBlockActionCallNamed asHBlockActionCallNamed(CBlocking::HBlock c);
		HBlockVariableNamed asHBlockVariableNamed(CBlocking::HBlock c);
		HBlockUnderstandDynamic asHBlockUnderstandDynamic(CBlocking::HBlock c);
		HBlockUnderstandStatic asHBlockUnderstandStatic(CBlocking::HBlock c);

		HBlockToDecideWhether asHBlockToDecideWhether(CBlocking::HBlock c);
		HBlockToDecideIf asHBlockToDecideIf(CBlocking::HBlock c);
		HBlockToDecideWhat_FirstNoum asHBlockToDecideWhat_FirstNoum(CBlocking::HBlock c);
		HBlockToDecideWhat asHBlockToDecideWhat(CBlocking::HBlock c);
		HBlockToDecideOn asHBlockToDecideOn(CBlocking::HBlock c);
		HBlockBooleanValue asHBlockBooleanValue(CBlocking::HBlock c);
		HBlockToDecide asHBlockToDecide(CBlocking::HBlock c);

		HBlockActionApply asHBlockActionApply(CBlocking::HBlock c);
		HBlockKindOfName asHBlockKindOfName(CBlocking::HBlock c);
		HBlockKindEntity asHBlockKindEntity(CBlocking::HBlock c);

		HBlockArgumentInput asHBlockArgumentInput(CBlocking::HBlock c);
		HBlockText asHBlockText(CBlocking::HBlock c);
		HBlockTextSentence asHBlockTextSentence(CBlocking::HBlock c);
		HBlockInstanceNamed asHBlockInstanceNamed(CBlocking::HBlock c);
		HBlockInstanceAnonymous asHBlockInstanceAnonymous(CBlocking::HBlock c);
		HBlockInstance asHBlockInstance(CBlocking::HBlock c);

		HBlockRelationBase asHBlockRelationBase(CBlocking::HBlock c);
		HBlockSimetricRelation asHBlockSimetricRelation(CBlocking::HBlock c);
		HBlockASimetricRelation asHBlockASimetricRelation(CBlocking::HBlock c);
		HBlockRelationInstance asHBlockRelationInstance(CBlocking::HBlock c);
		HBlockRelationArguments  asHBlockRelationArguments(CBlocking::HBlock c);

		HBlockVerbRelation asHBlockVerbRelation(CBlocking::HBlock c);
		HBlockVerbReverseRelation asHBlockVerbReverseRelation(CBlocking::HBlock c);
		HBlockAssertion_isConstantAssign asHBlockAssertion_isConstantAssign(CBlocking::HBlock c);
		HBlockAssertion_isForbiddenAssign asHBlockAssertion_isForbiddenAssign(CBlocking::HBlock c);
		HBlockAssertion_isVariable asHBlockAssertion_isVariable(CBlocking::HBlock c);
		HBlockAssertion_isNamedValueOf asHBlockAssertion_isNamedValueOf(CBlocking::HBlock c);
		HBlockAssertion_InstanceVariable asHBlockAssertion_InstanceVariable(CBlocking::HBlock c);
		HBlockAssertion_isInstanceOf asHBlockAssertion_isInstanceOf(CBlocking::HBlock c);
		HBlockDinamicDispatch asHBlockDinamicDispatch(CBlocking::HBlock c);
		HBlockNow asHBlockNow(CBlocking::HBlock c);
		HBlockBody    asHBlockBody(CBlocking::HBlock  c);
		HBlockEvery asHBlockEvery(CBlocking::HBlock c);

		HVariableSlotEnum asHVariableSlotEnum(HVariableSlot c);
		HVariableSlotBool asHVariableSlotBool(HVariableSlot c);

		HBlockControlToken asHBlockControlToken(CBlocking::HBlock c);
		HBlockControlIF asHBlockControlIF(CBlocking::HBlock c);
		HBlockControlSelect asHBlockControlSelect(CBlocking::HBlock c);
		HBlockControlSelectItem asHBlockControlSelectItem(CBlocking::HBlock c);
		HBlockComandList asHBlockComandList(CBlocking::HBlock c);
		HBlockControlIF asHBlockControlIF(CBlocking::HBlock c);
		HBlockControlForEach asHBlockControlForEach(CBlocking::HBlock c);
		HBlockRelationLookup asHBlockRelationLookup(CBlocking::HBlock c);
		HBlockVerbLookup asHBlockVerbLookup(CBlocking::HBlock c);
		HBlockSelector_Where asHBlockSelector_Where(CBlocking::HBlock c);
		HBlockSelectorAND asHBlockSelectorAND(CBlocking::HBlock c);


		HBlockNumber asHBlockNumber(CBlocking::HBlock c);

		HBlockExecutionResultFlag asHBlockExecutionResultFlag(CBlocking::HBlock c);



		HBlockVerbRelation    asHBlockVerbRelation(CBlocking::HBlock  c);
		HBlockAssertion_is    asHBlockAssertion_is(CBlocking::HBlock  c);
		HBlockMatch    asHBlockMatch(CBlocking::HBlock  c);
 
		HBlockComposition    asHBlockComposition(CBlocking::HBlock  c);
		HBlockRelationBase    asHBlockRelationBase(CBlocking::HBlock  c);
		HBlockToDecide    asHBlockToDecide(CBlocking::HBlock  c);
		HBlockKind    asHBlockKind(CBlocking::HBlock  c);
		HBlockInstance    asHBlockInstance(CBlocking::HBlock  c);
		HBlockNoum    asHBlockNoum(CBlocking::HBlock  c);
		HBlockNoumCompose    asHBlockNoumCompose(CBlocking::HBlock  c);
		HBlockValue    asHBlockValue(CBlocking::HBlock  c);
		HBlockSelector    asHBlockSelector(CBlocking::HBlock  c);
		HBlockActionCall    asHBlockActionCall(CBlocking::HBlock  c);
		HBlockNumber    asHBlockNumber(CBlocking::HBlock  c);
		HBlockMatchIs    asHBlockMatchIs(CBlocking::HBlock  c);
		HBlockAction    asHBlockAction(CBlocking::HBlock  c);
		HBlockList    asHBlockList(CBlocking::HBlock  c);
		HBlockAssertionBase    asHBlockAssertionBase(CBlocking::HBlock  c);
 
		HBlockKindOf    asHBlockKindOf(CBlocking::HBlock  c);
		HBlockKindNamed    asHBlockKindNamed(CBlocking::HBlock  c);
		HBlockKindAction    asHBlockKindAction(CBlocking::HBlock  c);
		HBlockKindEntity    asHBlockKindEntity(CBlocking::HBlock  c);
		HBlockKindValue    asHBlockKindValue(CBlocking::HBlock  c);
	 
		HBlockNamedValue    asHBlockNamedValue(CBlocking::HBlock  c);
		 
		HBlockInstanceVariable    asHBlockInstanceVariable(CBlocking::HBlock  c);
		HBlockList_OR    asHBlockList_OR(CBlocking::HBlock  c);
		HBlockList_AND    asHBlockList_AND(CBlocking::HBlock  c);
		HBlockEnums    asHBlockEnums(CBlocking::HBlock  c);
		HBlockProperty    asHBlockProperty(CBlocking::HBlock  c);
		HBlockAssertion_isDefaultAssign    asHBlockAssertion_isDefaultAssign(CBlocking::HBlock  c);
		HBlockKindReference    asHBlockKindReference(CBlocking::HBlock  c);
		HBlockKind_InstanceVariable    asHBlockKind_InstanceVariable(CBlocking::HBlock  c);
		HBlockAssertion_isDirectAssign    asHBlockAssertion_isDirectAssign(CBlocking::HBlock  c);
		HBlockAssertion_canBe    asHBlockAssertion_canBe(CBlocking::HBlock  c);
 
		HBlockIsVerb    asHBlockIsVerb(CBlocking::HBlock  c);
 
		HBlockIsNotVerb    asHBlockIsNotVerb(CBlocking::HBlock  c);
		
		HBlockMatchText    asHBlockMatchText(CBlocking::HBlock  c);
		HBlockMatchAny    asHBlockMatchAny(CBlocking::HBlock  c);
		HBlockMatchNamed    asHBlockMatchNamed(CBlocking::HBlock  c);
		HBlockMatchList    asHBlockMatchList(CBlocking::HBlock  c);
		HBlockMatchDirectIsNot    asHBlockMatchDirectIsNot(CBlocking::HBlock  c);
		 
		HBlockMatchKind    asHBlockMatchKind(CBlocking::HBlock  c);
		HBlockMatchProperty    asHBlockMatchProperty(CBlocking::HBlock  c);
		HBlockMatchBlock    asHBlockMatchBlock(CBlocking::HBlock  c);
		HBlockMatchOR    asHBlockMatchOR(CBlocking::HBlock  c);
		HBlockMatchAND    asHBlockMatchAND(CBlocking::HBlock  c);
		HBlockMatchDirectIs    asHBlockMatchDirectIs(CBlocking::HBlock  c);
		HBlockMatchIsVerb    asHBlockMatchIsVerb(CBlocking::HBlock  c);
		HBlockMatchIsNotVerb    asHBlockMatchIsNotVerb(CBlocking::HBlock  c);
		HBlockAssertion_isNotDirectAssign    asHBlockAssertion_isNotDirectAssign(CBlocking::HBlock  c);
		HBlockMatchNoum    asHBlockMatchNoum(CBlocking::HBlock  c);
		HBlockBooleanAND    asHBlockBooleanAND(CBlocking::HBlock  c);
		HBlockVerb    asHBlockVerb(CBlocking::HBlock  c);
		HBlockBooleanOR    asHBlockBooleanOR(CBlocking::HBlock  c);
		HBlockBooleanNOT    asHBlockBooleanNOT(CBlocking::HBlock  c);
		HBlockSelector_All    asHBlockSelector_All(CBlocking::HBlock  c);
		HBlockSelector_Any    asHBlockSelector_Any(CBlocking::HBlock  c);
		HBlockStaticDispatch    asHBlockStaticDispatch(CBlocking::HBlock  c);
		HBlockActionNamed    asHBlockActionNamed(CBlocking::HBlock  c);
		HBlockActionInstance    asHBlockActionInstance(CBlocking::HBlock  c);
		HBlockTryCall    asHBlockTryCall(CBlocking::HBlock  c);
		HBlockVariableNamed    asHBlockVariableNamed(CBlocking::HBlock  c);
		HBlockUnderstandDynamic    asHBlockUnderstandDynamic(CBlocking::HBlock  c);
		HBlockUnderstandStatic    asHBlockUnderstandStatic(CBlocking::HBlock  c);
		HBlockToDecideWhether    asHBlockToDecideWhether(CBlocking::HBlock  c);
		HBlockToDecideIf    asHBlockToDecideIf(CBlocking::HBlock  c);
		HBlockToDecideWhat_FirstNoum    asHBlockToDecideWhat_FirstNoum(CBlocking::HBlock  c);
		HBlockToDecideWhat    asHBlockToDecideWhat(CBlocking::HBlock  c);
		HBlockToDecideOn    asHBlockToDecideOn(CBlocking::HBlock  c);
		HBlockActionApply    asHBlockActionApply(CBlocking::HBlock  c);
		HBlockKindOfName    asHBlockKindOfName(CBlocking::HBlock  c);
		HBlockArgumentInput    asHBlockArgumentInput(CBlocking::HBlock  c);
		HBlockText    asHBlockText(CBlocking::HBlock  c);
		HBlockSimetricRelation    asHBlockSimetricRelation(CBlocking::HBlock  c);
		HBlockASimetricRelation    asHBlockASimetricRelation(CBlocking::HBlock  c);
		HBlockRelationInstance    asHBlockRelationInstance(CBlocking::HBlock  c);
		HBlockVerbDirectRelation    asHBlockVerbDirectRelation(CBlocking::HBlock  c);
		HBlockVerbReverseRelation    asHBlockVerbReverseRelation(CBlocking::HBlock  c);
		HBlockAssertion_isConstantAssign    asHBlockAssertion_isConstantAssign(CBlocking::HBlock  c);
		HBlockAssertion_isForbiddenAssign    asHBlockAssertion_isForbiddenAssign(CBlocking::HBlock  c);
		HBlockAssertion_isVariable    asHBlockAssertion_isVariable(CBlocking::HBlock  c);
		HBlockAssertion_isNamedValueOf    asHBlockAssertion_isNamedValueOf(CBlocking::HBlock  c);
		HBlockAssertion_InstanceVariable    asHBlockAssertion_InstanceVariable(CBlocking::HBlock  c);
		HBlockAssertion_isInstanceOf    asHBlockAssertion_isInstanceOf(CBlocking::HBlock  c);
		HBlockDinamicDispatch    asHBlockDinamicDispatch(CBlocking::HBlock  c);
		HBlockNow    asHBlockNow(CBlocking::HBlock  c);
		HBlockBody    asHBlockBody(CBlocking::HBlock  c);
		HBlockControlIF    asHBlockControlIF(CBlocking::HBlock  c);
		HBlockControlUnless    asHBlockControlUnless(CBlocking::HBlock  c);
		HBlockControlToken    asHBlockControlToken(CBlocking::HBlock  c);
		HBlockComandList    asHBlockComandList(CBlocking::HBlock  c);
		HBlockControlSelect    asHBlockControlSelect(CBlocking::HBlock  c);
		HBlockControlSelectItem    asHBlockControlSelectItem(CBlocking::HBlock  c);
		HBlockConditionalRelation    asHBlockConditionalRelation(CBlocking::HBlock  c);
		HBlockMatchNOT    asHBlockMatchNOT(CBlocking::HBlock  c);
		HBlockMatchWhich    asHBlockMatchWhich(CBlocking::HBlock  c);
		HBlockMatchWhichNot    asHBlockMatchWhichNot(CBlocking::HBlock  c);
		HBlockBooleanValue    asHBlockBooleanValue(CBlocking::HBlock  c);
		HBlockRelationLookup    asHBlockRelationLookup(CBlocking::HBlock  c);
		HBlockVerbLookup    asHBlockVerbLookup(CBlocking::HBlock  c);
		HBlockSelector_Where    asHBlockSelector_Where(CBlocking::HBlock  c);
		HBlockEvery    asHBlockEvery(CBlocking::HBlock  c);
		HBlockVerbConjugation    asHBlockVerbConjugation(CBlocking::HBlock  c);
		HBlockVerbAdapt    asHBlockVerbAdapt(CBlocking::HBlock  c);
		HBlockMatchActionCall    asHBlockMatchActionCall(CBlocking::HBlock  c);
		HBlockEventHandle    asHBlockEventHandle(CBlocking::HBlock  c);
		HBlockIntegerNumber    asHBlockIntegerNumber(CBlocking::HBlock  c);
		HBlockFactionalNumber    asHBlockFactionalNumber(CBlocking::HBlock  c);
		HBlockExecutionResultFlag    asHBlockExecutionResultFlag(CBlocking::HBlock  c);
		HBlockControlForEach    asHBlockControlForEach(CBlocking::HBlock  c);
		HBlockAssertion_isLocalVariable    asHBlockAssertion_isLocalVariable(CBlocking::HBlock  c);
		HBlockRelationArguments    asHBlockRelationArguments(CBlocking::HBlock  c);
		HBlockSelectorAND    asHBlockSelectorAND(CBlocking::HBlock  c);
		HBlockAssert    asHBlockAssert(CBlocking::HBlock  c);
		HBlockCompositionList    asHBlockCompositionList(CBlocking::HBlock  c);
		HBlockCompositionPhrase    asHBlockCompositionPhrase(CBlocking::HBlock  c);
		HBlockCompositionRelation    asHBlockCompositionRelation(CBlocking::HBlock  c);
		HBlockNothing    asHBlockNothing(CBlocking::HBlock  c);
 
		HBlockActionCallNamed    asHBlockActionCallNamed(CBlocking::HBlock  c);
		HBlockInstanceNamed    asHBlockInstanceNamed(CBlocking::HBlock  c);
		HBlockMatchValue    asHBlockMatchValue(CBlocking::HBlock  c);
		HBlockAnything    asHBlockAnything(CBlocking::HBlock  c);
		HBlockPhraseDefine    asHBlockPhraseDefine(CBlocking::HBlock  c);
		HBlockPhraseInvoke    asHBlockPhraseInvoke(CBlocking::HBlock  c);
		HBlockPhraseHeader    asHBlockPhraseHeader(CBlocking::HBlock  c);
		HBlockTextSentence    asHBlockTextSentence(CBlocking::HBlock  c);
		HBlockVerbNegate    asHBlockVerbNegate(CBlocking::HBlock  c);
		HBlockNoumSupl    asHBlockNoumSupl(CBlocking::HBlock  c);
		HBlockNoumStr    asHBlockNoumStr(CBlocking::HBlock  c);
		HBlockNoumStrDet    asHBlockNoumStrDet(CBlocking::HBlock  c);
		HBlockIsAdverbialComparasion    asHBlockIsAdverbialComparasion(CBlocking::HBlock  c);
		HBlockMatchIsAdverbialComparasion    asHBlockMatchIsAdverbialComparasion(CBlocking::HBlock  c);
		HBlockUnitInit    asHBlockUnitInit(CBlocking::HBlock  c);
		HBlockUnitTest    asHBlockUnitTest(CBlocking::HBlock  c);
		HBlockUnitAssert    asHBlockUnitAssert(CBlocking::HBlock  c);



	}
}

#endif