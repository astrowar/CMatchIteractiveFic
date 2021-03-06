#pragma once
#ifndef APPMATCH_BLOCKNAMEDVAR_H
#define APPMATCH_BLOCKNAMEDVAR_H

#include "BlockInterpreter.hpp"
#include <string>


namespace CBlocking
{
	//namespace VariableSloting {
	

		enum VarSlotType
		{
			EnumSlot,
			BoolSlot
		};

		class CVariableSlot {
		public:
			virtual ~CVariableSlot() {
			}
			virtual VarSlotType  type() = 0;
		};

		using HVariableSlot = std::shared_ptr<CVariableSlot>;

		class CVariableSlotEnum : public CVariableSlot {
		public:
			CBlocking::HBlockNoum value;
			CBlocking::HBlockEnums valueDefinition;

			CVariableSlotEnum(CBlocking::HBlockEnums enums);
			virtual VarSlotType  type() override { return VarSlotType::EnumSlot; };
		};

		using HVariableSlotEnum = std::shared_ptr<CVariableSlotEnum>;

		class CVariableSlotBool : public CVariableSlot {
		public:
			bool value;
			CBlocking::HBlockNoum valueDefinition;

			CVariableSlotBool(CBlocking::HBlockNoum valueDef);
			virtual VarSlotType  type() override { return VarSlotType::BoolSlot; };
		};

		using HVariableSlotBool = std::shared_ptr<CVariableSlotBool>;

		class CBlockVariableNamed :public  CBlock {
		public:
			void dump(string ident) override;
			virtual BlockType type() override { return BlockType::BlockVariableNamed; }

			CBlocking::HBlock value;
			CBlocking::HBlockKind kind;
			CBlocking::HBlockNoum name;
			CBlockVariableNamed(CBlocking::HBlockNoum _name, CBlocking::HBlockKind _kind, CBlocking::HBlock _value);
		};

		using HBlockVariableNamed = std::shared_ptr<CBlockVariableNamed>;

#endif

	}

//}