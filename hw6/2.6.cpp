#include <iostream>
#include <fstream>

int main( int argc , char * argv[] )
{

  std::ofstream fs( "foo.txt" );
  for( unsigned int i=2 ; i<argc ; i++ )
    {
      fs << argv[i];
      if( i==argc-1 ) fs << std::endl;
      else            fs << " ";
    }
  std::ifstream is( "foo.txt" );        //input stream
  std::string tmp , target( argv[1] );
  unsigned int targetCount = 0;
  while( is >> tmp ) if( tmp==target ) targetCount++;
  std::cout << "Found " << targetCount
            << " instances of \"" << target << "\"" << std::endl;
}

/*
Found 1 instances of "run"

fs takes all values from 2nd input word on
is is input stream for next word
tmp is first word of input
counts how many times the first word in the string appears in input
*/