epsDivD_list = logspace(-1, -6, 6);
Re_list = logspace(log10(4000), 8); % log(4000) = 3.6

figure;
for i = 1:size(epsDivD_list, 2)
    % setup
    epsDivD = epsDivD_list(i);
    f_list = repmat(0, size(Re_list,2));
    
    % calculate points
    for i = 1:size(Re_list,2)
        Re = Re_list(i);
        colebrook = @(f) 1/sqrt(f) + 2.0.*log10(epsDivD./3.7 + 2.51./(Re.*sqrt(f)));
        f_list(i) = fzero(colebrook, [1e-10,1]);
    end;
    
    % plot
    loglog(Re_list, f_list);
    hold on;
end;
title('Moody diagram');
xlabel('Reynolds number Re');
ylabel('Friction factor f');
legend('\epsilon/D = ' + string(epsDivD_list), 'Location', 'southwest');
