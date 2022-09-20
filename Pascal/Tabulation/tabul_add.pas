unit tabul_add;

interface

const
  maxpr = 8; //����������� ��������� ��������
  maxsteps = 30000;   //����������� ��������� ���-�� ����� � ������� ��������
  n_main_menu = 3; //���������� ������� �������� ����
  main_menu_list: array[1..n_main_menu] of string = (
    '������� �����������',
    '��������� ����������',
    '�����');
  n_set_menu = 6;  //���������� ������� ���� ��������
  set_menu_list: array[1..n_set_menu] of string = (
    '����� �������',
    '������� ����������',
    '��� �������� ���������',
    '���-�� ������ ����',
    '������ ����� �������',
    '����� � ������� ����');
  n_funct = 4;  //���������� �������
  funct_list: array [1.. n_funct] of string = (
    'exp(x)',
    'sin(x)',
    'cos(x)',
    'arctg(x)');
  def_set_list: array[1..n_funct, 1..3] of real = //(������������ ��������, ��� �� ���������) ��� ������ �������
  ((-20, 30, 1), 
  (-25, 25, 0.5), 
  (-25, 25, 0.5), 
  (-1, 1, 0.01));

type
  dif = function(x: real; n: byte; var c_err: real): real;//����������� ��� ��� ������ �������

var
  err: boolean;      // ��� �������� 
  input_val: string; // ������ �� �����
  
  pmenu: char; //����� ����� ����
  fchoice: dif; //�������
  fnum: byte; //����� ������� � �������
  lside: real; //����� ������� ��� ����������
  rside: real; //������ ������� ��� ����������
  lrange: real; //���������� ����. ���.
  rrange: real;// ����������� ����. ���.
  step: real; //��� ���.
  n_row: byte; //���������� ������ ����
  pr: byte; //��������
  
  tval: integer; // ���������������
  hv, hv1: real;//   ����������

function a_exp(x: real; n: byte; var c_err: real): real;
function a_sin(x: real; n: byte; var c_err: real): real;
function a_cos(x: real; n: byte; var c_err: real): real;
function a_arctg(x: real; n: byte; var c_err: real): real;
function strform(x: real; d: byte): string;
function  prec_round(var x: real; prec: byte): string;

implementation
//----------��������� ����� ������ �� ������� �������� (������������ ������ :a:b)--//
function strform(
                 x: real; //��������
                 d: byte) //��������
                 : string; //������ ��� ������
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
//-----------------���������� � �������� ��������� (������������ ���������� ���������� � ���������)----//
function  prec_round(
                     var x: real; //��������
                     prec: byte) //��������
                     : string; //������ �� ����� (�����������)
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
//-------���������� ��������� ��� sin x, cosx �� �������� � [0 , 2*pi]---//
procedure  fix_angle(
                     var x: real);//��������
begin
    while x < 0 do
      x += 2 * pi;
    while x > 2*pi do 
      x -= 2 * pi;
end;
//-------------------------------------------------//
//--------------���������� exp(x)------------------//
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
//--------------���������� sin(x)------------------//
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
//--------------���������� cos(x)------------------//
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
//--------------���������� arctg(x)------------------//
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