program compare_of_sort;

uses
  crt;

const
  num_max = 50000;  //наибольшее число элементов в массиве
  num_min = 1000; // наименьшее число элементов в массиве
  num_menu = 9;//число пунктов меню

type
  sort_types = ( //типы сортировок
  bubble,
  select, 
  insert, 
  merge,
  shell,
  quick);
  nvect = array [1..num_max] of integer;//для сортируемых массивов
  pmenu = array [1..num_menu] of string;//для заголовков меню
  psort = array [byte] of sort_types;//для хранения информации о том, какие были сортировки
  info_sort = array[byte] of word;//для хранения информации о времени сортировок, количестве элементов
//------Генерация массива по умолчанию--
procedure default_gen(var a: nvect);
var
  i: word;
begin
  for i := 1 to num_max do
    a[i] := num_max - i + 1;
end;
//--------------------------

//--------Меню--------------
function menu(names: pmenu; amount: byte; const a: nvect; n: word): char;
var
  i: byte;
  k: char;
begin
  clrscr;
  writeln('Текущий массив из ', n, ' элементов: ');
  writeln(a[1], ' ', a[2], ' . . .', a[n - 1], ' ', a[n]);
  writeln('------Меню------');
  for i := 1 to amount do
    writeln(i, '. ', names[i]);
  write('Выберите действие: ');
  readln(k);
  writeln;
  menu := k;
end;
//--------------------------

//---------Генерация массива с заданным числом элементов--
procedure arr_gen(var na: word; var a: nvect);
var
  i: word;
  temp: string;
  err: integer;
begin
  repeat
    clrscr;
    write('Введите количество элементов ', num_min, '..', num_max, ': ');
    readln(temp);
    val(temp, na, err);
    if (na > num_max) or (na < num_min) or (err > 0) then
    begin
      writeln('Неверное количество, повторите ввод.');
      readln;
    end;
  until (na <= num_max) and (na >= num_min) and (err = 0);
  randomize;
  for i := 1 to na do
  begin
    a[i] := random(2 * na) - na  + 1;
  end;
end;
//--------------------------

//---------Вывод таблицы результатов--
procedure print_res(count: byte; n: info_sort; names: psort; time: info_sort);
var
  i: byte;
begin
  clrscr;
  writeln('Элементов     Тип сортировки      Время');
  for i := 1 to count do
  begin
    gotoxy(3, i + 1);
    write(n[i]);
    gotoxy(19, i + 1);
    write(names[i]);
    gotoxy(35, i + 1);
    write(time[i]);
  end;
  writeln;
  write('Для выхода в меню нажмите любую клавишу.');
  readln;
end;
//--------------------------

//------Bubble--------------
procedure bubble_sort(n: word; var a: nvect);
var
  swaps: boolean;
  i, j: word;
begin 
  i:=0;
  swaps := true;
  while (i < n - 1) and swaps do
  begin
    swaps := false;
    inc(i);
    for j := 1 to n - i do
      if a[j] > a[j + 1] then 
      begin
        swaps := true;
        swap(a[j],a[j+1]);
      end;
  end;
end;
//--------------------------

//------Select--------------
procedure select_sort(n: word; var a: nvect);
var
  i, min, j: word;
  temp: integer;
begin
  for i := 1 to n - 1 do
  begin
    min := i;
    for j := i + 1 to n do
      if a[j] < a[min] then
        min := j;
    if min <> i then
    begin
      temp := a[i];
      a[i] := a[min];
      a[min] := temp;
    end;
  end;
end;
//--------------------------

//------Insert-------------
procedure insert_sort(n: word; var a: nvect);
  function bin_search(n: word; const a: nvect; el: integer): word;
  var
    st, mid, fn: word;
  begin
    st := 1;
    fn := n;
    while(st <= fn) do
    begin
      mid := (st + fn) div 2;
      if el > a[mid] then 
        st := mid + 1
      else fn := mid - 1;
    end;
    bin_search := st;
  end;
  
  procedure shift(k: word; fn: word; var a: nvect);
  var
    i: word;
  begin
    for i := fn downto k do 
      a[i + 1] := a[i];
  end;

var
  i, pos: word;
  r: integer;
begin
  for i := 2 to n do
  begin
    r := a[i];
    pos := bin_search(i - 1, a, r);
    shift(pos, i - 1, a);
    a[pos] := r;
  end;
end;
//-------------------------
var cop:nvect;
//------Merge--------------
procedure merge_sort(st, fn: word; var a: nvect);
var
  i, j, k, d, mid: word;
begin
  mid := (st + fn - 1) div 2;
  if mid - st > 0 then
    merge_sort(st, mid, a);
  if fn - mid > 1 then
    merge_sort(mid + 1, fn, a);
  j := mid + 1; i := st;
  k := st - 1;
  for d:=st to fn do
  cop[d]:=a[d];
  while(i <= mid) and (j <= fn) do
  begin
    inc(k);
    if cop[i] < cop[j] then
    begin
      a[k] := cop[i];
      inc(i);
    end
    else
    begin
      a[k] := cop[j];
      inc(j);
    end;
  end;
  if i <= mid then
    for j := i to mid do
    begin
      inc(k);
      a[k] := cop[j];
    end
  else
    for i := j to fn do
    begin
      inc(k);
      a[k] := cop[i];
    end;
end;
//-------------------------

//---------Shell-----------
procedure shell_sort(n: word; var a: nvect);
var
  d, i, j: word;
  temp: integer;
begin
  d := n;
  d := d div 2;
  while (d > 0) do
  begin
    for i := 1 to n - d do
    begin
      j := i;
      while ((j > 0) and (A[j] > A[j + d])) do
      begin
        temp := A[j];
        A[j] := A[j + d];
        A[j + d] := temp;
        j := j - 1;
      end;
    end;
    d := d div 2;
  end;
  
end;
//-------------------------

//---------Quick-----------
procedure quick_sort(st, fn: word; var a: nvect);
var
  l, r, i_op: word;
  temp, op: integer;
begin
  if fn - st > 0 then
  begin
    i_op := (st + fn - 1) div 2;
    op := a[i_op];
    l := st;
    r := fn;
    while(l < r) do
    begin
      while a[l] < op do
        inc(l);
      while a[r] > op do
        dec(r);
      if l < r then 
      begin
        temp := a[l];
        a[l] := a[r];
        a[r] := temp;
        if l = i_op then 
        begin
          inc(l);
          i_op := r;
        end
        else if r = i_op then
        begin
          dec(r);
          i_op := l;
        end
        else begin inc(l); dec(r); end;
      end;
    end;
  end;
  if l - st > 1 then 
    quick_sort(st, l - 1, a);
  if fn - l > 1 then
    quick_sort(l + 1, fn, a);
end;
//-------------------------

//-----Сортировка в общем виде--
procedure sort(dif: sort_types; n: word; var a: nvect; var name: sort_types; var time: word);
begin
  clrscr;
  write('Выполняется сортировка...');
  name := dif;
  time := milliseconds;
  case dif of
    bubble: bubble_sort(n, a);
    select: select_sort(n, a);
    insert: insert_sort(n, a);
    merge: merge_sort(1, n, a);
    shell: shell_sort(n, a);
    quick: quick_sort(1, n, a);
  end;
  time := milliseconds - time;
  clrscr;
  writeln('Отсортированный массив: ');
  writeln(a[1], ' ', a[2], ' . . .', a[n - 1], ' ', a[n]);
  writeln('Сортировка ', dif, ' массива из ', n, ' элементов заняла ', time, ' миллисекунд.');
  write('Для выхода в меню нажмите любую клавишу.');
  readln;
end;
//--------------------------

var
  menu_names: pmenu = (
                       'Сформировать новый массив',
                       'Результаты сортировок', 
                       'Сортировка пузырьком', 
                       'Сортировка выбором',
                       'Сортировка вставками(бинарный поиск)',
                       'Сортировка слиянием',
                       'Сортировка Шелла',
                       'Быстрая сортировка',
                       'Выход');
  menu_ch: char; // Переменная выбора пункта меню
  n_curr: word; // Количество элементов в текущем массиве
  arr_curr, dup: nvect; // Текущий массив
  test_n: info_sort; // Количество элементов для прошлых тестов
  test_names: psort; // Название сортировок прошлых тестов
  test_time: info_sort; // Время прошлых тестов
  test_amount: byte;// Количество тестов

begin
  n_curr := num_max;    // Генерация массива по умолчанию
  default_gen(arr_curr); //
  repeat
    menu_ch := menu(menu_names, num_menu, arr_curr, n_curr);
    
    if (menu_ch >= '3') and (menu_ch <= chr(ord('0') + ord(num_menu - 1))) then //Дупликация массива,увеличение кол-ва сортировок, 
    begin//если в меню была выбрана сортировка
      inc(test_amount);
      dup := arr_curr;
      test_n[test_amount] := n_curr;
    end;
    
    case menu_ch of
      '1': arr_gen(n_curr, arr_curr);
      '2': print_res(test_amount, test_n, test_names, test_time);
      '3': sort(bubble, n_curr, dup, test_names[test_amount], test_time[test_amount]);
      '4': sort(select, n_curr, dup, test_names[test_amount], test_time[test_amount]);
      '5': sort(insert, n_curr, dup, test_names[test_amount], test_time[test_amount]);
      '6': sort(merge, n_curr, dup, test_names[test_amount], test_time[test_amount]);
      '7': sort(shell, n_curr, dup, test_names[test_amount], test_time[test_amount]);
      '8': sort(quick, n_curr, dup, test_names[test_amount], test_time[test_amount]);
      '9':         ;
    else
      begin
        write('Неверный пункт меню, повторите ввод ');
        readln;
      end;
    end;
  until menu_ch = chr(ord('0') + ord(num_menu));
end.