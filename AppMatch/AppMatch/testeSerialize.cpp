#include "BaseTest.h"
#include <cassert>
#include "CDataMananger.h"
#include <fstream>


void testeSerialize1() {


	HBlockInterpreter interpreter = std::make_shared<CBlockInterpreter>();
	CParser parse(interpreter);



	auto p = (parse.parser_stmt("puting  is ( an action  applying to ( an thing ) and ( an thing)  )", ISLOG));
	
	//data_d_mananger.store( std::make_shared<CBlockNoum>("teste") );

	auto h = std::make_shared<CBlockNoum>("teste");

	 
	 
	
	return;

 

	 

}