<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3a" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_1" />
        <signal name="XLXN_2" />
        <signal name="XLXN_3" />
        <signal name="iD" />
        <signal name="XLXN_5" />
        <signal name="XLXN_6" />
        <signal name="XLXN_7" />
        <signal name="XLXN_8" />
        <signal name="XLXN_9" />
        <signal name="iA" />
        <signal name="iB" />
        <signal name="iC" />
        <signal name="oY" />
        <port polarity="Input" name="iD" />
        <port polarity="Input" name="iA" />
        <port polarity="Input" name="iB" />
        <port polarity="Input" name="iC" />
        <port polarity="Output" name="oY" />
        <blockdef name="m8_1e">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="96" y1="-224" y2="-224" x1="0" />
            <line x2="96" y1="-160" y2="-160" x1="0" />
            <line x2="96" y1="-96" y2="-96" x1="0" />
            <line x2="96" y1="-288" y2="-288" x1="0" />
            <line x2="96" y1="-352" y2="-352" x1="0" />
            <line x2="96" y1="-416" y2="-416" x1="0" />
            <line x2="96" y1="-544" y2="-544" x1="0" />
            <line x2="96" y1="-608" y2="-608" x1="0" />
            <line x2="96" y1="-672" y2="-672" x1="0" />
            <line x2="96" y1="-736" y2="-736" x1="0" />
            <line x2="96" y1="-160" y2="-160" x1="160" />
            <line x2="160" y1="-268" y2="-160" x1="160" />
            <line x2="96" y1="-224" y2="-224" x1="128" />
            <line x2="128" y1="-264" y2="-224" x1="128" />
            <line x2="96" y1="-96" y2="-96" x1="192" />
            <line x2="192" y1="-276" y2="-96" x1="192" />
            <line x2="96" y1="-32" y2="-32" x1="224" />
            <line x2="224" y1="-280" y2="-32" x1="224" />
            <line x2="256" y1="-512" y2="-512" x1="320" />
            <line x2="96" y1="-768" y2="-256" x1="96" />
            <line x2="96" y1="-704" y2="-768" x1="256" />
            <line x2="256" y1="-288" y2="-704" x1="256" />
            <line x2="256" y1="-256" y2="-288" x1="96" />
            <line x2="96" y1="-32" y2="-32" x1="0" />
            <line x2="96" y1="-480" y2="-480" x1="0" />
        </blockdef>
        <blockdef name="vcc">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-64" x1="64" />
            <line x2="64" y1="0" y2="-32" x1="64" />
            <line x2="32" y1="-64" y2="-64" x1="96" />
        </blockdef>
        <blockdef name="inv">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="160" y1="-32" y2="-32" x1="224" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="64" y1="0" y2="-64" x1="64" />
            <circle r="16" cx="144" cy="-32" />
        </blockdef>
        <block symbolname="m8_1e" name="XLXI_1">
            <blockpin signalname="XLXN_1" name="D0" />
            <blockpin signalname="XLXN_3" name="D1" />
            <blockpin signalname="iD" name="D2" />
            <blockpin signalname="iD" name="D3" />
            <blockpin signalname="XLXN_3" name="D4" />
            <blockpin signalname="XLXN_1" name="D5" />
            <blockpin signalname="iD" name="D6" />
            <blockpin signalname="iD" name="D7" />
            <blockpin signalname="XLXN_1" name="E" />
            <blockpin signalname="iA" name="S0" />
            <blockpin signalname="iB" name="S1" />
            <blockpin signalname="iC" name="S2" />
            <blockpin signalname="oY" name="O" />
        </block>
        <block symbolname="vcc" name="XLXI_4">
            <blockpin signalname="XLXN_1" name="P" />
        </block>
        <block symbolname="inv" name="XLXI_5">
            <blockpin signalname="iD" name="I" />
            <blockpin signalname="XLXN_3" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="2032" y="1488" name="XLXI_1" orien="R0" />
        <branch name="XLXN_1">
            <wire x2="1520" y1="496" y2="752" x1="1520" />
            <wire x2="2032" y1="752" y2="752" x1="1520" />
            <wire x2="1520" y1="752" y2="1072" x1="1520" />
            <wire x2="1520" y1="1072" y2="1456" x1="1520" />
            <wire x2="2032" y1="1456" y2="1456" x1="1520" />
            <wire x2="2032" y1="1072" y2="1072" x1="1520" />
        </branch>
        <branch name="XLXN_3">
            <wire x2="1920" y1="560" y2="816" x1="1920" />
            <wire x2="2032" y1="816" y2="816" x1="1920" />
            <wire x2="1920" y1="816" y2="1008" x1="1920" />
            <wire x2="2032" y1="1008" y2="1008" x1="1920" />
            <wire x2="2080" y1="560" y2="560" x1="1920" />
            <wire x2="2080" y1="464" y2="464" x1="2064" />
            <wire x2="2080" y1="464" y2="560" x1="2080" />
        </branch>
        <branch name="iD">
            <wire x2="1792" y1="416" y2="464" x1="1792" />
            <wire x2="1792" y1="464" y2="880" x1="1792" />
            <wire x2="2016" y1="880" y2="880" x1="1792" />
            <wire x2="2032" y1="880" y2="880" x1="2016" />
            <wire x2="1792" y1="880" y2="944" x1="1792" />
            <wire x2="2032" y1="944" y2="944" x1="1792" />
            <wire x2="1792" y1="944" y2="1136" x1="1792" />
            <wire x2="2032" y1="1136" y2="1136" x1="1792" />
            <wire x2="1792" y1="1136" y2="1200" x1="1792" />
            <wire x2="2032" y1="1200" y2="1200" x1="1792" />
            <wire x2="1840" y1="464" y2="464" x1="1792" />
        </branch>
        <iomarker fontsize="28" x="1792" y="416" name="iD" orien="R270" />
        <instance x="1456" y="496" name="XLXI_4" orien="R0" />
        <instance x="1840" y="496" name="XLXI_5" orien="R0" />
        <branch name="iA">
            <wire x2="2032" y1="1264" y2="1264" x1="2000" />
        </branch>
        <iomarker fontsize="28" x="2000" y="1264" name="iA" orien="R180" />
        <branch name="iB">
            <wire x2="2032" y1="1328" y2="1328" x1="2000" />
        </branch>
        <iomarker fontsize="28" x="2000" y="1328" name="iB" orien="R180" />
        <branch name="iC">
            <wire x2="2032" y1="1392" y2="1392" x1="2000" />
        </branch>
        <iomarker fontsize="28" x="2000" y="1392" name="iC" orien="R180" />
        <branch name="oY">
            <wire x2="2384" y1="976" y2="976" x1="2352" />
        </branch>
        <iomarker fontsize="28" x="2384" y="976" name="oY" orien="R0" />
    </sheet>
</drawing>