function [ o ] = tacho2pot( u )
    global V_s;
    global K_rev;
    
    o = (-V_s + 2*mod(u*(V_s/K_rev) + V_s/2, V_s));
end

