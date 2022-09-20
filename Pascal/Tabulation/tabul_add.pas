unit tabul_add;

interface

const
  maxpr = 8; //Максимально возможная точность
  maxsteps = 30000;   //Максимально возможное кол-во строк в таблице значений
  n_main_menu = 3; //Количество пунктов главного меню
  main_menu_list: array[1..n_main_menu] of string = (
    'Таблица результатов',
    'Параметры вычисления',
    'Выход');
  n_set_menu = 6;  //Количество пунктов меню настроек
  set_menu_list: array[1..n_set_menu] of string = (
    'Выбор функции',
    'Границы вычисления',
    'Шаг значения агрумента',
    'Кол-во членов ряда',
    'Знаков после запятой',
    'Выход в главное меню');
  n_funct = 4;  //Количество функций
  funct_list: array [1.. n_funct] of string = (
    'exp(x)',
    'sin(x)',
    'cos(x)',
    'arctg(x)');
  def_set_list: array[1..n_funct, 1..3] of real = //(Максимальный диапазон, шаг по умолчанию) для четырёх функций
  ((-20, 30, 1), 
  (-25, 25, 0.5), 
  (-25, 25, 0.5), 
  (-1, 1, 0.01));

type
  dif = function(x: real; n: byte; var c_err: real): real;//Процедурный тип для выбора функции

var
  err: boolean;      // Для проверки 
  input_val: string; // ошибки во вводе
  
  pmenu: char; //Выбор пукта меню
  fchoice: dif; //Функция
  fnum: byte; //Номер функции в всписке
  lside: real; //Левая граница для вычислений
  rside: real; //Правая граница для вычислений
  lrange: real; //Минимально возм. арг.
  rrange: real;// Максимально возм. арг.
  step: real; //Шаг арг.
  n_row: byte; //Количество членов ряда
  pr: byte; //Точность
  
  tval: integer; // Вспомогательные
  hv, hv1: real;//   переменные

function a_exp(x: real; n: byte; var c_err: real): real;
function a_sin(x: real; n: byte; var c_err: real): real;
function a_cos(x: real; n: byte; var c_err: real): real;
function a_arctg(x: real; n: byte; var c_err: real): real;
function strform(x: real; d: byte): string;
function  prec_round(var x: real; prec: byte): string;

implementation
//----------Формирует часть строки из таблицы значений (некорректная работа :a:b)--//
function strform(
                 x: real; //Значение
                 d: byte) //Точность
                 : string; //Строка для вывода
var
  res: string;
  i: byte;
begin
  str(x:26:d, res);
  res := trim(res);
  for i := 1 to 26 - length(res) do
    res += ' ';
  strform := res;
end;
//------------------------------------------------------------------------------//
//-----------------Округление с заданной точностью (некорректные результаты вычислений и сравнений)----//
function  prec_round(
                     var x: real; //Значение
                     prec: byte) //Точность
                     : string; //Строка на вывод (опционально)
var
  temp: string;
  i: byte;
begin
  str(x:3 + prec:prec, temp);
  temp := trim(temp);
  i := length(temp);
  while temp[i] = '0'  do 
  begin
    delete(temp, i, 1);
    dec(i);
  end;
  if temp[i] = '.' then delete(temp, i, 1);
  x := strtofloat(temp);
  prec_round := temp;
end;
//-----------------------------------------------------------------------//
//-------Исправляет аргументы для sin x, cosx не входящие в [0 , 2*pi]---//
procedure  fix_angle(
                     var x: real);//Значение
begin
    while x < 0 do
      x += 2 * pi;
    while x > 2*pi do 
      x -= 2 * pi;
end;
//-------------------------------------------------//
//--------------Вычисление exp(x)------------------//
function a_exp(x: real; n: byte; var c_err: real): real;
var
  i: byte;
  sum, cur: real;
begin
  cur := 1;
  for i := 1 to n do
  begin
    sum += cur;
    cur *= x / i;
  end;
  c_err := abs(exp(x) - sum);
  a_exp := sum;
end;
//-------------------------------------------------//
//--------------Вычисление sin(x)------------------//
function a_sin(x: real; n: byte; var c_err: real): real;
var
  i: byte;
  sum, cur: real;
begin
  fix_angle(x);
  cur := x;
  sum := cur;
  for i := 2 to n do
  begin
    cur *= -x * x / ((2 * i - 2) * (2 * i - 1));
    sum += cur;
  end;
  c_err := abs(sin(x) - sum);
  a_sin := sum;
end;
//-------------------------------------------------//
//--------------Вычисление cos(x)------------------//
function a_cos(x: real; n: byte; var c_err: real): real;
var
  i: byte;
  sum, cur: real;
begin
  fix_angle(x);
  cur := 1;
  for i := 1 to n do
  begin
    sum += cur;
    cur *= -x * x /( (2 * i)*(2*i-1));
  end;
  c_err := abs(cos(x) - sum);
  a_cos := sum;
end;
//---------------------------------------------------//
//--------------Вычисление arctg(x)------------------//
function a_arctg(x: real; n: byte; var c_err: real): real;
var
  i: byte;
  sum, cur: real;
begin
  cur := x;
  sum := cur;
  for i := 2 to n do
  begin
    cur *= -x * x / (2 * i - 1);
    sum += cur;
  end;
  c_err := abs(arctan(x) - sum);
  a_arctg := sum;
end;
//--------------------------------------------------//
begin
end. 