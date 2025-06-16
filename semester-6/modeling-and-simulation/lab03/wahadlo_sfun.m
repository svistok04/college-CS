function wahadlo_sfun(block)
    % incjalizacja bloku i wykresu
    setup(block);
    % dodanie funkcji do aktualizacji wykresu
    block.RegBlockMethod('Update'  ,@update);
end

%==============================================================

function setup(block)
    % konfiguracja wyjsc
    block.NumOutputPorts = 0;
    % konfigruacja wejsc
    block.NumInputPorts  = 1;
    block.InputPort(1).Dimensions = 1;
    block.InputPort(1).DirectFeedthrough = true;
    % czas probkowana (wejscie, wyjscie)
    block.SampleTimes = [0.01 0];
    % stany dyskretne
    block.NumDworks = 0;
    % stale przekazane do sfunkcji
    block.NumDialogPrms = 3;
    
    % przygotowanie okna do dalszej wizualizacji
    L   = block.DialogPrm(1).Data;
    m   = block.DialogPrm(2).Data;
    fi0 = block.DialogPrm(3).Data;
    initFigure(L, m, fi0);
end

%==============================================================

function initFigure(L, m, fi0)
    close all
    FigureName = 'Wizualizacja wahadla';
    Fig = figure('Name', FigureName);
    fi0 = fi0 * pi / 180;
    % Pierwsze rysowanie wahad³a
    p = plot([0 -L*sin(fi0)],[0 -L*cos(fi0)],'Color','r','LineWidth',2);
    hold on
    s = plot(-L*sin(fi0), -L*cos(fi0), 'b.','MarkerSize',5*m);
    hold off
    % Ustawienia osi
    axis([-1.1*L 1.1*L -1.1*L 1.1*L])
    set(gca,'DataAspectRatio',[1 1 1])
    set(gca,'XTick',[-L 0 L],'YTick',[-L 0 L])
    % Zapamiêtanie uchwytów na wykresy
    FigUD.p = p;
    FigUD.s = s;
    set(Fig,'UserData',FigUD);
    set_param(gcbh,'UserData',Fig);
end

%==============================================================

function update(block)
    fi = block.InputPort(1).Data;
    L   = block.DialogPrm(1).Data;
    m   = block.DialogPrm(2).Data;

    fig = get_param(gcbh,'UserData');
    if ishandle(fig)
         ud = get(fig,'UserData');
         % Aktualizacja rysunku
         set(ud.s, 'XData', -L*sin(fi), 'YData', -L*cos(fi)) ;
         set(ud.p, 'XData', [0 -L*sin(fi)], 'YData', [0 -L*cos(fi)]) ;
         drawnow
    end
end