<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="spartan3a" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="iB(0)">
        </signal>
        <signal name="XLXN_37" />
        <signal name="iB(1)" />
        <signal name="oY(2)" />
        <signal name="oY(0)" />
        <signal name="iA(0)">
        </signal>
        <signal name="oY(1)" />
        <signal name="o1" />
        <signal name="o3" />
        <signal name="oY(3)" />
        <signal name="XLXN_49" />
        <signal name="o4" />
        <signal name="o2" />
        <signal name="iA(1:0)" />
        <signal name="oY(3:0)" />
        <signal name="iB(1:0)" />
        <signal name="XLXN_55" />
        <port polarity="Input" name="XLXN_37" />
        <port polarity="Input" name="iB(1)" />
        <port polarity="Output" name="oY(2)" />
        <port polarity="Output" name="oY(0)" />
        <port polarity="Output" name="oY(1)" />
        <port polarity="Output" name="oY(3)" />
        <port polarity="Input" name="iA(1:0)" />
        <port polarity="Output" name="oY(3:0)" />
        <port polarity="Input" name="iB(1:0)" />
        <blockdef name="and2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <arc ex="144" ey="-144" sx="144" sy="-48" r="48" cx="144" cy="-96" />
            <line x2="64" y1="-48" y2="-48" x1="144" />
            <line x2="144" y1="-144" y2="-144" x1="64" />
            <line x2="64" y1="-48" y2="-144" x1="64" />
        </blockdef>
        <blockdef name="xor2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="60" y1="-128" y2="-128" x1="0" />
            <line x2="208" y1="-96" y2="-96" x1="256" />
            <arc ex="44" ey="-144" sx="48" sy="-48" r="56" cx="16" cy="-96" />
            <arc ex="64" ey="-144" sx="64" sy="-48" r="56" cx="32" cy="-96" />
            <line x2="64" y1="-144" y2="-144" x1="128" />
            <line x2="64" y1="-48" y2="-48" x1="128" />
            <arc ex="128" ey="-144" sx="208" sy="-96" r="88" cx="132" cy="-56" />
            <arc ex="208" ey="-96" sx="128" sy="-48" r="88" cx="132" cy="-136" />
        </blockdef>
        <block symbolname="and2" name="XLXI_1">
            <blockpin signalname="iB(0)" name="I0" />
            <blockpin signalname="iA(0)" name="I1" />
            <blockpin signalname="oY(0)" name="O" />
        </block>
        <block symbolname="xor2" name="XLXI_9">
            <blockpin signalname="o3" name="I0" />
            <blockpin signalname="o1" name="I1" />
            <blockpin signalname="oY(1)" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_5">
            <blockpin signalname="o3" name="I0" />
            <blockpin signalname="o1" name="I1" />
            <blockpin signalname="o2" name="O" />
        </block>
        <block symbolname="xor2" name="XLXI_8">
            <blockpin signalname="o4" name="I0" />
            <blockpin signalname="o2" name="I1" />
            <blockpin signalname="oY(2)" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_6">
            <blockpin signalname="o4" name="I0" />
            <blockpin signalname="o2" name="I1" />
            <blockpin signalname="oY(3)" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_2">
            <blockpin signalname="iB(1)" name="I0" />
            <blockpin signalname="iA(0)" name="I1" />
            <blockpin signalname="o1" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_3">
            <blockpin signalname="iB(0)" name="I0" />
            <blockpin signalname="XLXN_55" name="I1" />
            <blockpin signalname="o3" name="O" />
        </block>
        <block symbolname="and2" name="XLXI_4">
            <blockpin signalname="iB(1)" name="I0" />
            <blockpin signalname="XLXN_37" name="I1" />
            <blockpin signalname="o4" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <branch name="iB(0)">
            <wire x2="944" y1="1296" y2="1296" x1="912" />
        </branch>
        <branch name="XLXN_37">
            <wire x2="944" y1="1536" y2="1536" x1="880" />
        </branch>
        <branch name="iB(1)">
            <wire x2="944" y1="1600" y2="1600" x1="880" />
        </branch>
        <branch name="oY(2)">
            <wire x2="1984" y1="1264" y2="1264" x1="1968" />
            <wire x2="2080" y1="1264" y2="1264" x1="1984" />
        </branch>
        <branch name="oY(0)">
            <wire x2="1216" y1="752" y2="752" x1="1200" />
            <wire x2="2080" y1="752" y2="752" x1="1216" />
            <wire x2="2096" y1="752" y2="752" x1="2080" />
        </branch>
        <branch name="iB(0)">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="912" y="784" type="branch" />
            <wire x2="928" y1="784" y2="784" x1="912" />
            <wire x2="944" y1="784" y2="784" x1="928" />
        </branch>
        <branch name="iA(0)">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="912" y="720" type="branch" />
            <wire x2="928" y1="720" y2="720" x1="912" />
            <wire x2="944" y1="720" y2="720" x1="928" />
        </branch>
        <instance x="944" y="848" name="XLXI_1" orien="R0" />
        <branch name="iA(0)">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="896" y="960" type="branch" />
            <wire x2="944" y1="960" y2="960" x1="896" />
        </branch>
        <branch name="iB(1)">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="896" y="1024" type="branch" />
            <wire x2="944" y1="1024" y2="1024" x1="896" />
        </branch>
        <instance x="1376" y="1120" name="XLXI_9" orien="R0" />
        <branch name="oY(1)">
            <wire x2="1648" y1="1024" y2="1024" x1="1632" />
            <wire x2="2080" y1="1024" y2="1024" x1="1648" />
        </branch>
        <branch name="o1">
            <wire x2="1328" y1="992" y2="992" x1="1200" />
            <wire x2="1328" y1="992" y2="1200" x1="1328" />
            <wire x2="1344" y1="1200" y2="1200" x1="1328" />
            <wire x2="1376" y1="992" y2="992" x1="1328" />
        </branch>
        <branch name="o3">
            <wire x2="1280" y1="1264" y2="1264" x1="1200" />
            <wire x2="1344" y1="1264" y2="1264" x1="1280" />
            <wire x2="1280" y1="1056" y2="1264" x1="1280" />
            <wire x2="1376" y1="1056" y2="1056" x1="1280" />
        </branch>
        <instance x="1344" y="1328" name="XLXI_5" orien="R0" />
        <instance x="1712" y="1360" name="XLXI_8" orien="R0" />
        <instance x="1696" y="1632" name="XLXI_6" orien="R0" />
        <branch name="oY(3)">
            <wire x2="1968" y1="1536" y2="1536" x1="1952" />
            <wire x2="2080" y1="1536" y2="1536" x1="1968" />
        </branch>
        <instance x="944" y="1088" name="XLXI_2" orien="R0" />
        <instance x="944" y="1360" name="XLXI_3" orien="R0" />
        <instance x="944" y="1664" name="XLXI_4" orien="R0" />
        <branch name="o4">
            <wire x2="1520" y1="1568" y2="1568" x1="1200" />
            <wire x2="1568" y1="1568" y2="1568" x1="1520" />
            <wire x2="1600" y1="1568" y2="1568" x1="1568" />
            <wire x2="1696" y1="1568" y2="1568" x1="1600" />
            <wire x2="1712" y1="1296" y2="1296" x1="1600" />
            <wire x2="1600" y1="1296" y2="1568" x1="1600" />
        </branch>
        <branch name="o2">
            <wire x2="1680" y1="1232" y2="1232" x1="1600" />
            <wire x2="1712" y1="1232" y2="1232" x1="1680" />
            <wire x2="1680" y1="1232" y2="1504" x1="1680" />
            <wire x2="1696" y1="1504" y2="1504" x1="1680" />
        </branch>
        <branch name="iA(1:0)">
            <wire x2="1040" y1="480" y2="480" x1="912" />
        </branch>
        <branch name="oY(3:0)">
            <wire x2="1408" y1="464" y2="464" x1="1184" />
        </branch>
        <branch name="iB(1:0)">
            <wire x2="1024" y1="592" y2="592" x1="880" />
        </branch>
        <iomarker fontsize="28" x="880" y="1536" name="XLXN_37" orien="R180" />
        <iomarker fontsize="28" x="880" y="1600" name="iB(1)" orien="R180" />
        <iomarker fontsize="28" x="2096" y="752" name="oY(0)" orien="R0" />
        <iomarker fontsize="28" x="2080" y="1264" name="oY(2)" orien="R0" />
        <iomarker fontsize="28" x="912" y="480" name="iA(1:0)" orien="R180" />
        <iomarker fontsize="28" x="1408" y="464" name="oY(3:0)" orien="R0" />
        <iomarker fontsize="28" x="880" y="592" name="iB(1:0)" orien="R180" />
        <iomarker fontsize="28" x="2080" y="1024" name="oY(1)" orien="R0" />
        <iomarker fontsize="28" x="2080" y="1536" name="oY(3)" orien="R0" />
        <branch name="XLXN_55">
            <wire x2="944" y1="1232" y2="1232" x1="896" />
        </branch>
    </sheet>
</drawing>