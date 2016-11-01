#include "BaseTest.hpp"
#include <cassert>


void testeExecute1() 
{

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);
	string ss1 =
		R"( 
the verb (points to)  implies a  dynamic relation
value is a kind of value
x is a value
x can be a , b or c
x is c
route is a kind 
room is a kind 
route has a room called destination
route has a room called origin

definition : ( ( route called PATH ) points to ( room called R ) ) if ( ( destination of PATH ) is R )
definition : ( route called PATH ) is viable exit  if (( destination of PATH ) is not limbo) and ( ( destination of PATH ) is not location ) 
      

garden is a room
hall is a room
door is a route
destination of door is garden
limbo is a room
location is a room that varies
location is hall

Connection relates (a room ) to  ( a room )
the verb connect   implies a  Connection relation

hall connect garden

)";
	//definition : ( ( route called PATH ) points to ( room called R ) ) if ( ( destination of PATH ) is R )
	string ss2 =
		R"(
if x is :
   -- a : now x points to b
   -- b : now x is c
   -- c :  
         now x is a
          
else:  
   say  ( text error )
)";

	printf("=========================================\n");
	auto stmt = parse.parser_text(ss1, ISLOG);

	interpreter->execute_init(stmt);
	

	//auto ret_e = interpreter->query(parse.Parser_Stmt(" x is c  ", ISLOG));
//	assert(ret_e == QEquals);

	//auto ret_dst = interpreter->query(parse.Parser_Stmt("destination of door is garden  ", ISLOG));
	//assert(ret_dst == QEquals);

	auto query_block = parse.Parser_Stmt("door points to garden  ", ISLOG);
	auto ret_points = interpreter->query(query_block);
	assert(ret_points == QEquals);

	 
	auto ret_points_q = interpreter->query(parse.Parser_Stmt("door points to hall  ", ISLOG));
	assert(ret_points_q == QNotEquals);

	auto ret_points_init = interpreter->query(parse.Parser_Stmt("door is viable exit ", ISLOG));
	assert(ret_points_init == QEquals);

	interpreter->execute_now(parse.Parser_Stmt("location is garden ", ISLOG));
	auto ret_points_garden = interpreter->query(parse.Parser_Stmt("door is viable exit  ", ISLOG));
	assert(ret_points_garden == QNotEquals);

	auto ret_connect_init = interpreter->query(parse.Parser_Stmt("hall connect garden ", ISLOG));
	assert(ret_connect_init == QEquals);

	return;
}


void testeExecute2()
{

	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);
	string ss1 =
			R"(

room is a kind
garden is a room
hall is a room 
Connection relates ( a room ) to  ( a room )
the verb connect   implies a  Connection relation 
hall connect garden

)";


	auto stmt = parse.parser_text(ss1, ISLOG);

	interpreter->execute_init(stmt);


	auto ret_connect_init = interpreter->query(parse.Parser_Stmt("hall connect garden ", ISLOG));
	assert(ret_connect_init == QEquals);

	auto ret_connect_b = interpreter->query(parse.Parser_Stmt("garden connect hall  ", ISLOG));
	assert(ret_connect_b == QNotEquals  );

	return;
}


void testeExecute3()
{
	// Teste do evaluate 
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);
	string ss1 =
		R"(
route is a kind 
room is a kind 
route has a room called destination
garden is a room
hall is a room 
exit is a route
destination of exit is garden
Connection relates ( a room called source ) to  ( a room called destination )
the verb connect   implies a  Connection relation 
hall connect garden
garden connect hall

direction  is a kind 
direction has a direction called ops

Oposition relates ( a direction  ) to   ( a direction called opposite )
the verb opposte by implies a  Oposition relation 

north is a direction
south is a direction
east  is a direction
west is a direction

)";
 

	interpreter->execute_init(parse.parser_text(ss1, false));

	//auto ret_1 = interpreter->evaluate_values(parse.Parser_Expression("source of garden", false ));
	//printf("=============================\n");
	//ret_1->dump(" ");

//	auto ret_2 = interpreter->evaluate_values(parse.Parser_Expression("destination of exit", false));
	//printf("=============================\n");
	//ret_2->dump(" ");

	

	//interpreter->execute_init(parse.Parser_Stmt("to decide what ( room  ) is oposite of ( oposite of ( room called X ) ) :  X   ", ISLOG));
	//auto ret_3 = interpreter->evaluate_values(parse.Parser_Expression("oposite of ( oposite of  garden) ", ISLOG));
	//printf("=============================\n");
	//ret_3->dump(" ");


	interpreter->execute_init(parse.Parser_Stmt("to decide if ( direction called Y ) is opposite of (  direction called X )   :  X is opposite of Y   ", ISLOG));	
	interpreter->execute_init(parse.Parser_Stmt("south is  opposte by  north", ISLOG));
	interpreter->execute_init(parse.Parser_Stmt(" west  is opposte by  east ", ISLOG));

	//auto ret_4 = interpreter->evaluate_values(parse.Parser_Expression("oposite of north  ", ISLOG));
	//printf("=============================\n");
	//ret_4->dump(" ");
	auto ret_true_a = interpreter->query(parse.Parser_Stmt("north is  opposite  of south  ", ISLOG));
	auto ret_true_b = interpreter->query(parse.Parser_Stmt("south is  opposite  of north  ", ISLOG));
	 auto ret_true_ba = interpreter->query(parse.Parser_Stmt(" south is  opposite  of ( opposite of  south ) ", ISLOG));
	assert(ret_true_a == QEquals);
	assert(ret_true_ba == QEquals);
 
	 
 
}


void testeExecute4()
{
	// Teste do evaluate 
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

	string ss1 =
		R"(
object is a kind 
book is a object
key is a object
box is a object
target is a object that varies
target is box 
)";

	interpreter->execute_init(parse.parser_text(ss1, ISLOG));

	string ss2 =
		R"(
if ( target ) is key :
   decide on book
else : 
   decide on target
)";

	

	auto target_q = interpreter->exec_eval(parse.parser_text(ss2, true), nullptr);
	target_q->dump("");
	//assert(ret_true_a == QEquals);
	return;
}



void testeExecute5()
{
	// Teste do evaluate 
	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);

	string ss1 =
		R"(
object is a kind 
object can be small or huge
object is usually  small
book is a object
key is a object
box is a object
target is a object that varies
target is box 

a talent is a kind of value
a talent can be normal 
strength, courage, luck, scent, honor, spirit and freedom is talent
luck is normal
)";

	interpreter->execute_init(parse.parser_text(ss1, ISLOG));

	if(true){
		string ss2 = R"(now every object is huge)";
		auto res_q = interpreter->query(parse.Parser_Stmt("box is small ", true));
		auto target_q = interpreter->exec_eval(parse.parser_text(ss2, true), nullptr);
		//target_q->dump("");
		//assert(ret_true_a == QEquals);
		auto res_2 = interpreter->query(parse.Parser_Stmt("box is huge ", true));
		assert(res_2 == QEquals);
	}

	if (true)
	{
		auto res_3 = interpreter->query(parse.Parser_Stmt("courage is not normal ", true));
		assert(res_3 == QNotEquals);
		//string ss3 = R"(now every talent is not normal )"; 
		interpreter->exec_eval(parse.parser_text("now every talent is not  normal", true), nullptr);
		res_3 = interpreter->query(parse.Parser_Stmt("courage is not normal ", true));
		assert(res_3 == QEquals);
	}

	return;
}
void testeExecute_all()
{
 
	testeExecute5();
	 
	   // testeExecute1();  precisa ser revisto o DEFINE
	 testeExecute2();
	testeExecute3();
		 testeExecute4();
		 
}