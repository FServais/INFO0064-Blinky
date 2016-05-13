function main(x, y, v, c, e, dispBool)

   plot(x, y, 'Og');
   hold on;

   [T1, T2] = sim_TD(x,y,v,c,e);
   
   [TD_x, TD_y] = solve_TD(T1,T2,v,c);
   
   if ~isreal(TD_x),
       disp('TD_x not real for point ');
       display(TD_x);
       display(x);
       display(y);
   elseif ~isreal(TD_y),
       disp('TD_y not real for point ');
       display(TD_y);
       display(x);
       display(y);
   else
      plot(TD_x, TD_y, '+r');
      hold on;

      if dispBool,
         display(T1);
         display(T2);
         display(TD_x);
         display(TD_y);
         disp('erreur = ');
         disp(sqrt((x - TD_x)^2 + (y - TD_y)^2));
      end
   end
end
