#include <iostream>
#include <string>
#include <iomanip>
#include <codecvt>

class BadLengthExc : public std::exception{
  public:
    const char* what() const noexcept override {
      return "Вы ввели слово запретной длины!";
    }
};

int function(std::string str, int forbidden_length);

int main() {
  //setlocale( LC_ALL,"Russian" );
  int forbidden_length {};
  std::cout<<"Введите запретную длину: ";
  std::cin >> forbidden_length;
  while(1){
    std::string word;
    std::cout<<"Введите слово: ";
    std::cin >> std::setw(255) >>word;
    int lngth {};
    try{
      lngth = function(word,forbidden_length);
    }catch(BadLengthExc &bdlen){
      std::cout << bdlen.what() << " До свидания\n";
      return 0;
    }catch(...){
      std::cout << "Неизвестная ошибка" << std::endl;
    }
    std::cout<<"Длина слова \""<<word<<"\" равна "<<lngth<<"\n";
  }
}

int function(std::string str, int forbidden_length){
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
  //https://stackoverflow.com/questions/2573834/c-convert-string-or-char-to-wstring-or-wchar-t
  std::wstring wstr = converter.from_bytes(str);
  if(wstr.length() != forbidden_length){
    return wstr.length();
  }else{
    throw BadLengthExc();
  }
}
