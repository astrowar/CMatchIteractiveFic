#include "BaseTest.hpp"
#include <cassert>

using namespace CBlocking;
using namespace Interpreter;
using namespace NSParser;


void testValues_1()
{
	
	// Values Testes

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;

	string s_heat = R"(
thing is a kind
 
ice cube is a thing


Heat is a kind of value
The heat are frosty, cold, cool, room temperature, warm, hot  and scalding
thing has a heat 
The heat of a thing is usually room temperature

apple is a thing
  
)";
	 

	interpreter->execute_init(ParseText::parser_text(&parse,s_heat, ISLOG));
	auto e = interpreter->exec_eval(Expression::Parser_Expression(&parse,"heat of ice cube ", ISLOG), nullptr, nullptr);
	auto ev = interpreter->exec_eval(Expression::Parser_Expression(&parse,"heat of apple  ", ISLOG), nullptr, nullptr);

	assert(e != nullptr);
	assert(ev != nullptr);
	

	e->dump("");
	ev->dump("");

	return;


}

void testValues_2() //numeric values
{
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	string s_price = R"(

The current size is a number that varies
current size is 20
device is a kind
battery is a device
The battery has a number called charge

)";


	interpreter->execute_init(ParseText::parser_text(&parse,s_price, ISLOG));
	auto ev = interpreter->exec_eval(Expression::Parser_Expression(&parse,"current size  ", ISLOG), nullptr,nullptr);
	auto ev2 = interpreter->exec_eval(Expression::Parser_Expression(&parse,"charge of battery  ", ISLOG), nullptr,nullptr);
	auto ev3 = interpreter->exec_eval(Expression::Parser_Expression(&parse,"list of thing   ", true), nullptr,nullptr);

	assert(ev != nullptr);
	assert(ev2 != nullptr);
	ev->dump("");
	ev2->dump("");
	ev3->dump("");
	return;

}

void testValues_1a()
{

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse;
	std::function<bool(std::string)> f_is = [&](std::string a) { return  interpreter->query(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr).result == QEquals; };
	std::function<HBlock(std::string)> f_eval = [&](std::string a) { return  interpreter->exec_eval(Expression::Parser_Expression(&parse, a, false), nullptr, nullptr); };
	std::function<PhaseResult(std::string)> f_now = [&](std::string a) { return  interpreter->execute_now(Statement::Parser_Stmt(&parse, a, false)); };


	string ss1 =
		R"(

thing is a kind 
ice cube is a thing
Heat is a kind of value
The heat are frosty, cold, cool, room temperature, warm, hot  and scalding
thing has a heat 
The heat of a thing is usually room temperature

apple is a thing

)";

	interpreter->execute_init(ParseText::parser_text(&parse, ss1, true));
	//f_eval("heat of ice cube  ")->dump("E ");
	assert(f_is("heat of ice cube is room temperature "));

 
}
void testValues_all()
{
	testValues_1a();
	//testValues_1();
	//testValues_2();
}