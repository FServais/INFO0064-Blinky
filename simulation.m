function simulation(v,c,e)

  x = -5 : 1 : 5;
  y =  0 : 1 : 5;
  
  for i = x;
      for j = y;
          main(i, j, v, c, e, false);
      end
  end
  
end
