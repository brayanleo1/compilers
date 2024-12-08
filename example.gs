main() begin
  float x := 1.;
  float y := 4;
  char c := "3";

  if (x>=y)
    if (x>y)
      print((x**2 - y) + c);
    end if

    if (y>x)
      print(x);
    end if
  end if

  if (c>y)
    print(c);
    print(y);
  end if

  print(c+y);
end main