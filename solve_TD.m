function [x, y] = solve_TD(T1, T2, v, c)
   x = -1;
   y = -1;
   
   d1 = T1 * v;
   d2 = T2 * v;

%%
%   syms x y;
%   eqn = [d1 == sqrt(x^2 + y^2) + sqrt((x - c)^2 + y^2), d2 == sqrt(x^2 + y^2) + sqrt((x + c)^2 + y^2)];
%   [solx, soly] = solve(eqn, [x, y]);
% 
%   x = eval(solx);
%   y = eval(soly);
% 
%   if (y(1) >= 0)
%       x = x(1);
%       y = y(1);
%   else
%       x = x(2);
%       y = y(2);
%   end

%% old
   e = c;

   if d1 == d2,
       x = 0;
       y = (d1^2 - e^2) / (2 * d1);
   else
       m = e^2 - d1^2;
       n = e^2 - d2^2;

       a = (n / d2^2) - (m / d1^2);
       b = -e*((n / d2^2) + (m / d1^2));
       c = (n^2 / (4 * d2^2)) - (m^2 / (4 * d1^2));

       delta = b^2 - 4 * a * c;

       if delta > 0,
           x = (-b + sqrt(delta)) / (2 * a);
           if ((m * x^2 + m * e * x + m^2 / 4) / d1^2) > 0,
              y = sqrt((m * x^2 + m * e * x + m^2 / 4) / d1^2);
           else
               disp('Warning sqrt arg negatif.');
               y = -1;
           end
       elseif delta == 0,
           disp('Warning, delta = 0');
           x = (-b) / (2 * a);
           y = sqrt((m * x^2 + m * e * x + m^2 / 4) / d1^2);
       else
           disp('Warning: delta negatif.');
           x = -1;
           y = -1;
       end
   end

%% Correct ? => not correct
%    e = c;
% 
%    if d1 == d2,
%        x = 0;
%        y = (d1^2 - e^2) / (2 * d1);
%    else
%        m = e^2 - d1^2;
%        n = e^2 - d2^2;
% 
%        a = (n / d2^2) - (m / d1^2);
%        b = e * ((n / d2^2) + (m / d1^2));
%        c = (n^2 / (4 * d2^2)) - (m^2 / (4 * d1^2));
% 
%        delta = b^2 - 4 * a * c;
% 
%        if delta > 0,
%            x = (-b + sqrt(delta)) / (2 * a);
%            if ((m * x^2 + m * e * x + m^2 / 4) / d1^2) > 0,
%               y = sqrt((m * x^2 + m * e * x + m^2 / 4) / d1^2);
%            else
%                disp('Warning sqrt arg negatif.');
%                y = -1;
%            end
%        elseif delta == 0,
%            disp('Warning, delta = 0');
%            x = (-b) / (2 * a);
%            y = sqrt((m * x^2 + m * e * x + m^2 / 4) / d1^2);
%        else
%            disp('Warning: delta negatif.');
%            x = -1;
%            y = -1;
%        end
%    end

end
