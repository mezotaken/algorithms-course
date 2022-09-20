program tabulation;

uses
  crt,tabul_add;
//-----------------Вычисление значений и вывод таблицы-------------------//
procedure draw_table(
                     f: dif;  //Выбранная функция
                     fn: byte; //Номер ф-ии в списке
                     l, // Начальное значение аргумента
                     r, // Конечное значение аргумента
                     s:real; // Шаг аргумента
                     n: byte; // Слагаемых Ряда Тейлора
                     d: byte); //Точность
var
  calc_err, cur: real;
  i: word;
begin
  clrscr;
  writeln('Таблица значений функции y = ', funct_list[fn], ':');
  writeln;
  writeln(' Аргумент                  Функция                   Погрешность');
  cur := l;
  for i := 1 to round((r - l) / step) do
  begin
    writeln(' ', strform(cur, d), strform(f(cur, n, calc_err), d), strform(calc_err, d));
    cur += step;
  end;
  writeln(' ', strform(r, d), strform(f(r, n, calc_err), d), strform(calc_err, d));
  writeln;
  write('Для выхода в главное меню нажмите любую клавишу.');
  readln;
end;
//-----------------------------------------------------------------//
//---------------------Вывод информации справа меню----------------//
procedure draw_info(
                    f: byte; //Номер ф-ии в списке
                    l, //Нач. зн. арг.
                    r, // Кон. зн. арг.
                    s: real; //Шаг арг.
                    n: byte; // Слаг. в Ряду Тейлора 
                    d: byte); //Точность
var
  sh: byte;
begin
  sh := 30;
  gotoxy(sh, 1);
  write('Текущие параметры: ');
  gotoxy(sh, 2);
  write('Функция: ', funct_list[f]);
  gotoxy(sh, 3);
  write('Границы вычислений: ', prec_round(l, pr), '...', prec_round(r, pr));
  gotoxy(sh, 4);
  write('Шаг значения агрумента: ', prec_round(s, pr));
  gotoxy(sh, 5);
  write('Кол-во членов ряда: ', n);
  gotoxy(sh, 6);
  write('Знаков после запятой: ', d);
  writeln;
end;
//--------------------------------------------------------------//
//---------------------Главное меню-----------------------------//
function main_menu(
                   f: byte; //Номер ф-ии в списке
                   l, //Нач. зн. арг.
                   r, // Кон. зн. арг.
                   s: real; //Шаг арг.
                   n: byte; // Слаг. в Ряду Тейлора 
                   d: byte) //Точность
                   : char; //Возвращает выбранный пункт меню.
var
  i: byte;
  c: char;
begin
  clrscr;
  writeln('     Главное меню');
  for i := 1 to n_main_menu do 
    writeln(' ', i, '. ', main_menu_list[i]);
  draw_info(f, l, r, s, n, d);
  write( 'Выберите пункт меню: ');
  readln(c);
  main_menu := c;
end;
//--------------------------------------------------------------//
//-------------------Меню параметров----------------------------//
function set_menu(
                   f: byte; //Номер ф-ии в списке
                   l, //Нач. зн. арг.
                   r, // Кон. зн. арг.
                   s: real; //Шаг арг.
                   n: byte; // Слаг. в Ряду Тейлора 
                   d: byte) //Точность
                   : char; //Возвращает выбранный пункт меню.
var
  i: byte;
  c: char;
begin
  clrscr;
  writeln(' Меню параметров вычисления');
  for i := 1 to n_set_menu do
    writeln(' ', i, '. ', set_menu_list[i]);
  draw_info(f, l, r, s, n, d);
  writeln;
  write( ' Выберите пункт меню: ');
  readln(c);
  set_menu := c;
end;
//--------------Меню выбора функции---------------------//
function funct_choice_menu:  
                          char; //Возвращает выбранный пункт меню 
var
  i: byte;
  c: char;
begin
  clrscr;
  for i := 1 to n_funct do
    writeln(i, '. ', funct_list[i]);
  write('Выберите функцию: ');
  readln(c);
  funct_choice_menu := c;
end;
//-----------------------------------------------------//
//----------------Основная программа-------------------//
begin
  //-----------Установка параметров по умолчанию-------//
  fchoice := a_exp;
  fnum := 1;
  lrange := def_set_list[fnum, 1];
  rrange := def_set_list[fnum, 2];
  lside := lrange;
  rside := rrange;
  step := def_set_list[fnum, 3];
  n_row := 255;
  pr := maxpr;
  //--------------------------------------------------//
  //---------------------Диалоговый раздел------------//
  repeat
    pmenu := main_menu(fnum, lside, rside, step, n_row, pr);
    case pmenu of
      '1': draw_table(fchoice, fnum, lside, rside, step, n_row, pr);
      '2': 
        repeat
          pmenu := set_menu(fnum, lside, rside, step, n_row, pr); 
          case pmenu of 
            '1': 
              begin
                repeat
                  pmenu := funct_choice_menu;
                  case pmenu of
                    '1': begin fchoice := a_exp; fnum := 1; end;
                    '2': begin fchoice := a_sin; fnum := 2; end;
                    '3': begin fchoice := a_cos; fnum := 3; end;
                    '4': begin fchoice := a_arctg; fnum := 4; end;
                  else 
                    begin
                      write('Неверный пункт меню. Повторите ввод.');
                      readln;
                    end; 
                  end;
                until not (err);
                lrange := def_set_list[fnum, 1];
                rrange := def_set_list[fnum, 2];
                lside := lrange;
                rside := rrange;
                step := def_set_list[fnum, 3];
              end;
            '2':   
              begin
                repeat
                  clrscr;
                  writeln('Введите левую границу: [', lrange, ' .. ', rrange, '), с точностью до ', pr, '^-10: ');
                  
                  readln(input_val);
                  err := not (trystrtofloat(input_val, lside)); 
                  prec_round(lside, pr);
                  if (lside >= rrange) or (lside < lrange) then
                    err := true;
                  if err then 
                  begin
                    write('Неверное значение, повторите ввод');
                    readln;
                  end;
                until not (err);
                repeat
                  clrscr;
                  writeln('Введите правую границу (', prec_round(lside, pr), ' .. ', rrange, '], с точностью до ', pr, '^-10: ');
                  readln(input_val);
                  err := not (trystrtofloat(input_val, rside));
                  prec_round(rside, pr);
                  if (rside <= lside) or (rside > rrange) then 
                    err := true;
                  if err then 
                  begin
                    write('Неверное значение, повторите ввод');
                    readln;
                  end;
                  
                until not (err);
                hv := rside - lside;
                prec_round(hv, pr);
                if step > hv then
                  step := hv;                
              end;
            '3': 
              begin
                hv := rside - lside;
                hv1 := hv / maxsteps;
                repeat
                  clrscr;             
                  writeln('Введите шаг значения аргумента (', prec_round(hv1, pr), ' .. ', prec_round(hv, pr), '], с точностью до ', pr, '^-10: ');
                  readln(input_val);
                  err := not (trystrtofloat(input_val, step));
                  prec_round(step, pr);
                  
                  if (step <= hv1) or (step > hv) then 
                    err := true;
                  if err then 
                  begin
                    write('Неверное значение, повторите ввод');
                    readln;
                  end;
                until not (err);
              end;
            '4': 
              begin
                repeat
                  clrscr;
                  write('Введите количество членов отрезка ряда 1 .. 255: ');
                  readln(input_val);
                  err := not (trystrtoint(input_val, tval));
                  if tval <= 0 then 
                    err := true;
                  if err then 
                  begin
                    write('Неверное значение, повторите ввод');
                    readln;
                  end;
                until not (err);
                n_row := tval;
              end;
            '5': 
              begin
                repeat
                  clrscr;
                  write('Введите количество знаков после запятой 3 .. ', maxpr, ': ');
                  readln(input_val);
                  err := not (trystrtoint(input_val, tval));
                  if (tval > maxpr) or (tval < 3) then
                    err := true;
                  if err then 
                  begin
                    write('Неверное значение, повторите ввод');
                    readln;
                  end;
                until not (err);
                pr := tval;
              end;
            '6':             ;
          else
            begin
              write('Неверный пункт меню. Повторите ввод.');
              readln;
            end; 
          end;
        until ord(pmenu) - ord('0') = n_set_menu;
      '3':             ;
    else 
      begin
        write('Неверный пункт меню. Повторите ввод.');
        readln;
      end; 
    end;
  until ord(pmenu) - ord('0') = n_main_menu;
end.