function simulation(v,c,e)

  x = -(10.0 + c) : 0.5 : +(10.0 + c);
  y =        +0.5 : 0.5 : +(20.5 + (2 * c));
  
  for i = x;
      for j = y;
          main(i, j, v, c, e, false);
      end
  end
  
end
