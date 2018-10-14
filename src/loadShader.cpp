#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <GL/glew.h>

#include <common/loadShader.hpp>

GLuint LoadShaders( const std::string& vertex_file_path
                  , const std::string& fragment_file_path
                  )
{
  using namespace std;

  // Create the shaders
  GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

  // Read the Vertex Shader code from the file
  string VertexShaderCode;
  ifstream VertexShaderStream(vertex_file_path.c_str(), ios::in);

  if(VertexShaderStream.is_open())
  {
    stringstream sstr;
    sstr << VertexShaderStream.rdbuf();
    VertexShaderCode = sstr.str();
    VertexShaderStream.close();
  }
  else
  {
    cerr  <<  "Impossible to open " << vertex_file_path << ". "
              "Are you in the right directory ? "
              "Don't forget to read the FAQ !\n";
    getchar();
    return 0;
  }

  // Read the Fragment Shader code from the file
  string FragmentShaderCode;

  ifstream FragmentShaderStream(fragment_file_path, ios::in);

  if(FragmentShaderStream.is_open())
  {
    stringstream sstr;
    sstr << FragmentShaderStream.rdbuf();
    FragmentShaderCode = sstr.str();
    FragmentShaderStream.close();
  }

  GLint Result = GL_FALSE;
  int InfoLogLength;

  // Compile Vertex Shader
  cout << "Compiling shader : " << vertex_file_path << endl;

  const auto VertexSourcePointer = VertexShaderCode.c_str();

  glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
  glCompileShader(VertexShaderID);

  // Check Vertex Shader
  glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

  if(InfoLogLength > 0)
  {
    vector<char> VertexShaderErrorMessage(InfoLogLength + 1);

    glGetShaderInfoLog( VertexShaderID
                      , InfoLogLength
                      , NULL
                      , VertexShaderErrorMessage.data()
                      );

    printf("%s\n", &VertexShaderErrorMessage[0]);
  }

  // Compile Fragment Shader
  cout << "Compiling shader : " << fragment_file_path << endl;

  const auto FragmentSourcePointer = FragmentShaderCode.c_str();

  glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
  glCompileShader(FragmentShaderID);

  // Check Fragment Shader
  glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

  if(InfoLogLength > 0)
  {
    vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);

    glGetShaderInfoLog( FragmentShaderID
                      , InfoLogLength
                      , NULL
                      , FragmentShaderErrorMessage.data()
                      );

    printf("%s\n", FragmentShaderErrorMessage.data());
  }

  // Link the program
  cout << "Linking program\n";
  GLuint ProgramID = glCreateProgram();
  glAttachShader(ProgramID, VertexShaderID);
  glAttachShader(ProgramID, FragmentShaderID);
  glLinkProgram(ProgramID);

  // Check the program
  glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
  glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);

  if(InfoLogLength > 0)
  {
    vector<char> ProgramErrorMessage(InfoLogLength + 1);

    glGetProgramInfoLog ( ProgramID
                        , InfoLogLength
                        , NULL
                        , ProgramErrorMessage.data()
                        );

    printf("%s\n", &ProgramErrorMessage[0]);
  }

  glDetachShader(ProgramID, VertexShaderID);
  glDetachShader(ProgramID, FragmentShaderID);

  glDeleteShader(VertexShaderID);
  glDeleteShader(FragmentShaderID);

  return ProgramID;
}
