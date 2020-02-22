// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   CoreWar.js                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2020/02/24 16:48:31 by laleta            #+#    #+#             //
//   Updated: 2020/02/24 16:58:47 by laleta           ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

const	loadProc_msg = "∘ loading champions code...";
const	loadPause_msg = "∘ loading champions code paused...";
const	warProc_msg = "∘ core war is running...";
const	warPause_msg = "∘ core war is paused...";
const	warFin_msg = "∘ program is complete...";
const	players = champion.length;
const	cycle_cnt = cycle.length;
const	oper_step = 3;
const	memory_step = 2;

let	cursorBlinkID;
let	loadIntervalID;
let	warIntervalID;
let firstIntervalID;
let printIntervalID;
let	operLine_cnt = 4;
let paused = 0;
let start = 0;
let step = 0;
let	speed = 1;
let mem_curr = [];
let mem_prev = [];
let ctd = cycle[0][2][0];
let ctd_curr = ctd;
let	opacity = [1];
let	idx;
let	cnt;
let oper_curr;
let	oper_prev;
let	player_n;
let	oper_n;
let	i = 0;

window.addEventListener("keydown", {handleEvent(event){key_event(event)}});

setTimeout(function() {print_str("Wake up, peer...", 4);
	setTimeout(function() {print_str("The CoreWar has you...", 4);
		setTimeout(function() {$("#select").slideToggle("slow", "linear");}, 4000);}, 4000);}, 2000);

firstIntervalID = setInterval(first_open, 0);

//-----------------------------------------------------------------------------
function key_event(event)
//-----------------------------------------------------------------------------
{
	if (event.keyCode == '27')
		$("#frame").toggle("slow", "linear", function(){window.close();});
	else if (step == 0 && event.keyCode == '89')
		start = 1;
	else if (step == 0 && event.keyCode == '78')
		start = -1;
	else if (event.keyCode == '80')
	{
		if (paused)
		{
			if (step == 1)
				start_load();
			else if (step == 2)
				start_war();
		}
		else
			if (step == 1)
				pause_load();
			else if (step == 2)
				pause_war();
	}
	else if (event.keyCode == '77')
		document.getElementById('audio_main').muted = true;
	else if (event.keyCode == '78')
		document.getElementById('audio_main').muted = false;
	else if (event.keyCode == '38' && speed < 10)
	{
		speed++;
		$("#speed" + speed).css("opacity", "1");
		document.getElementById("speed_value").innerHTML = "∘ " + (speed * 10)+" %";
	}
	else if (event.keyCode == '40' && speed > 1)
	{
		$("#speed" + speed).css("opacity", "0.2");
		speed--;
		document.getElementById("speed_value").innerHTML = "∘ " + (speed * 10)+" %";
	}
}

function pause_load()
{   
	paused = 1;
	document.getElementById('audio_main').pause();
	clearInterval(loadIntervalID);
	print_str(loadPause_msg, 0);
}

function start_load()
{
	paused = 0;
	document.getElementById('audio_main').play();
	loadIntervalID = setInterval(load_players, 0);
	print_str(loadProc_msg, 0);
}

function pause_war()
{
	paused = 1;
	document.getElementById('audio_main').pause();
	clearInterval(warIntervalID);
	print_str(warPause_msg, 1);
}

function start_war()
{
	paused = 0;
	document.getElementById('audio_main').play();
	warIntervalID = setInterval(war_cycle, 0);
	print_str(warProc_msg, 1);
}

//-----------------------------------------------------------------------------
function first_open()
//-----------------------------------------------------------------------------
{
	if (start == 1)
	{
		clearInterval(firstIntervalID);
		$("#start").css("display", "none");
		document.getElementById('start').remove();
		$("#select").slideToggle("slow", "linear", function(){
			document.getElementById('select').remove();
			step = 1;
			set_memTable();
			set_infoBox();
			start_load();});
	}
	else if (start == -1)
		$("#frame").toggle("slow", "linear", function(){window.close();});
}

//-----------------------------------------------------------------------------
function set_memTable()
//-----------------------------------------------------------------------------
{
	let	left_pos = 0;
	let	top_pos = 0;
	let	row = 4032;
	let	col = 4032;
	let	j = 0;

    while (j < 4096)
    {
        $("#memory").append("<div class=\"char\" id=\"char"+row+"\"> </div>");
        $("#char" + row).css("left", left_pos + "px");
        $("#char" + row).css("top", top_pos + "px");
        left_pos = left_pos + 25;
        row -= 64;
        j++;
        if (j % 64 == 0)
        {
            left_pos = 0;
            top_pos = top_pos + 20;
            row = col + 1;
            col = row;
        }
    }
}

//-----------------------------------------------------------------------------
function set_infoBox()
//-----------------------------------------------------------------------------
{
    let j = 0; 
	let	oper_id = 0;

    while (j <= 64)
    {
		if (j > 0)
			$("#operation_table").append("<div class=\"op_pl\" id=\"op_pl" + j + "\">" + bytecode[oper_id] + "</div>");
		if (!(j % 16) && j != 64)
		{
			$("#operation_table").append("<br>");
			oper_id = 0;
		}
		if (j > 0 && j <= 10)
			$("#speed").append("<div class=\"speed_bar\" id=\"speed" + j + "\"><div>");
		if (j < 4)
		{
			$("#player").append("<div class=\"player_data\" id=\"player" + j + "\"><div>");
			$("#player" + j).append("<div class=\"player_nbr\" id=\"player_nbr" + j + "\"><div>");
			$("#player" + j).append("<div class=\"player_name\" id=\"player_name" + j + "\"><div>");
			$("#player" + j).append("<div class=\"player_comment\" id=\"player_comment" + j + "\"><div>");
			$("#player" + j).append("<div class=\"player_barBorder\" id=\"player_barBorder" + j + "\"><div>");
			$("#player" + j).append("<div class=\"player_bar\" id=\"player_bar" + j + "\"><div>");
        	$("#state").append("<div class=\"str\" id=\"str" + j + "\"><div>");
            $("#operation_list").append("<div class=\"operation_line\" id=\"operation_line" + j + "\">∘ </div>");
		}
        j++;
		oper_id++;
    }
}

//-----------------------------------------------------------------------------
function print_str(str, n)
//-----------------------------------------------------------------------------
{
    let j = 0;

	if (n < 2 && step < 3 && n == step - 1)
		clearInterval(printIntervalID);
	document.getElementById('audio_print').play();
    $("#str" + n).html("");
    $("#str" + n).append("<div class=\"substr\" id=\"substr" + n + "\"></div>");
    $("#str" + n).append("<div class=\"cursor\" id=\"cursor" + n + "\"></div>");
    cursor_blink(n);
 	printIntervalID = setInterval(print_char, 90);
    function print_char()
    {
        $("#substr" + n).append(str[j]);
        j++;
        if (j == str.length)
			clearInterval(printIntervalID);
    }
}

//-----------------------------------------------------------------------------
function cursor_blink(n)
//-----------------------------------------------------------------------------
{
    let n_prev = n - 1;
    if (n > 0)
    {
        clearInterval(cursorBlinkID);
        $("#cursor" + n_prev).css("background-color", "black");
        $("#cursor" + n_prev).css("display", "none");
    }
    cursorBlinkID = setInterval(cursor_light, 800);
    function cursor_light()
    {
        $("#cursor" + n).fadeIn("fast", "linear").delay(500).fadeOut("fast", "linear");
    }
}

//-----------------------------------------------------------------------------
function load_players()
//-----------------------------------------------------------------------------
{
	let	player_nbr = 1;

	while (player_nbr <= players)
	{
		set_player(i, player_nbr, players);
		player_nbr++;
	}
	i++;
	if (i == CHAMP_MAX_SIZE + 1)
	{
		clearInterval(loadIntervalID);
		step = 2;
		core_war();
	}
}

function	set_player(i, player_nbr, player_cnt)
{
	let byte_n = i + (player_nbr - 1) * ((MEM_SIZE / player_cnt) | 0);
	let byte = memory_init[byte_n];
	let	byte_prev;

	if (byte >= 1000)
		byte = byte % 1000;
	if (byte_n > 0)
	{
		byte_prev = byte_n - 1;
		$("#char" + byte_prev).css("background-color", "black");
	}
	if (byte)
		$("#char" + byte_n).css("background-color", "lime");
	document.getElementById("char" + byte_n).innerHTML = bytecode[byte];
}

//-----------------------------------------------------------------------------
function core_war()
//-----------------------------------------------------------------------------
{
    let j = 0;

	document.getElementById("allCycle_value").innerHTML = cycle_cnt;;
	while (j < 4096)
	{
		mem_prev[j] = memory_init[j];
		j++;
	}
	j = 0;
    while (j < players)
    {
		document.getElementById("player_name" + j).innerHTML = champion[j][0].substring(0,38);
		document.getElementById("player_comment" + j).innerHTML = "//" + champion[j][1].substring(0,46);
		document.getElementById("player_nbr" + j).innerHTML = champion[j][2];
        j++;
    }
	i = 1;
    start_war();
}


//-----------------------------------------------------------------------------
function war_cycle()
//-----------------------------------------------------------------------------
{
	document.getElementById("cycle_value").innerHTML = i;
	document.getElementById("cycle_to_die").innerHTML = cycle[i][2][0];
	document.getElementById("cyclePr_value").innerHTML = ((100 * i / cycle_cnt) >> 0) + " %";

	idx = 1;
	while (idx <= 64)
	{
		$("#op_pl" + idx).css("background-color", "black");
		$("#op_pl" + idx).css("color", "lime");
		idx++;
	}

	idx = 1;
	while (i > 0 && idx < cycle[i][0].length)
	{
		oper_prev = cycle[i - 1][0][idx];
		oper_curr = cycle[i][0][idx];
		player_n = cycle[i][0][idx + 1];
		oper_n = (player_n - 1) * 16 + oper_curr;
		if (oper_curr > 0 && oper_curr < 17)
		{
			$("#op_pl" + oper_n).css("background-color", "lime");
			$("#op_pl" + oper_n).css("color", "black");
		}
		if (i > 0 && cycle[i][0][idx] == 0 && oper_prev < 17 && oper_prev > 0)
		{
			cnt = operLine_cnt - 4;
			document.getElementById("operation_line" + cnt).remove();
			$("#operation_list").append("<div class=\"operation_line\" id=\"operation_line" + operLine_cnt + "\"></div>");
			$("#operation_line" + operLine_cnt).append(operations[oper_prev]);
			operLine_cnt++;
		}
		idx = idx + oper_step;
	}

	mem_curr = mem_prev.slice(0);

	idx = 0;
	while (i < cycle_cnt && idx < cycle[i][1].length && cycle[i][1].length != 0)
	{
		mem_curr[cycle[i][1][idx]] = cycle[i][1][idx + 1];
		idx = idx + memory_step;
	}

	idx = 0;
	cnt = 0;
	while ((speed == 1 || !(i % (speed * 3))) && idx < MEM_SIZE && i < cycle_cnt)
	{
		byte = mem_curr[idx];
		if (byte >= 1000)
		{
			$("#char" + idx).css("background-color", "lime");
			$("#char" + idx).css("color", "black");
			cnt = cnt + ((byte - (byte % 1000)) / 1000);
			byte = byte % 1000;
		}
		else
		{
			$("#char" + idx).css("background-color", "black");
			$("#char" + idx).css("color", "lime");
		}
		if (i == 1 || mem_prev[idx] != byte)
		{
			document.getElementById("char" + idx).innerHTML = bytecode[byte];
			$("#char" + idx).css("opacity", 1);
			opacity[idx] = 1;
		}
		else
		{
			if (opacity[idx] > 0.4)
			{
				opacity[idx] = opacity[idx] - 0.005;
				$("#char" + idx).css("opacity", opacity[idx]);
			}
		}
		document.getElementById("process_value").innerHTML = cnt;
		idx++;
	}

	mem_prev = mem_curr.slice(0);

	function draw_ctd()
	{
		if (ctd_curr >= ctd * 0.75 && ctd_curr <= ctd * 0.9)
			$("#cycle_sector").css("border-top", "70px solid lime");
		else if (ctd_curr > ctd * 0.5 && ctd_curr <= ctd * 0.75)
			$("#cycle_sector").css("border-right", "70px solid lime");
		else if (ctd_curr > ctd * 0.25 && ctd_curr <= ctd * 0.5)
			$("#cycle_sector").css("border-bottom", "70px solid lime");
		else if (ctd_curr < ctd * 0.25)
			$("#cycle_sector").css("border-left", "70px solid lime");
		if (ctd_curr > ctd * 0.9)
		{
			$("#cycle_sector").css("border-top", "70px solid transparent");
			$("#cycle_sector").css("border-left", "70px solid transparent");
			$("#cycle_sector").css("border-bottom", "70px solid transparent");
			$("#cycle_sector").css("border-right", "70px solid transparent");
		}
		if (ctd_curr == 0)
		{
			ctd = cycle[0][2][0];
			ctd_curr = ctd;
		}
		ctd_curr--;
	}

	function draw_cycle()
	{
		if (i >= cycle_cnt * 0.1 && i <= cycle_cnt * 0.25)
			$("#cycleAll_sector").css("border-top", "70px solid lime");
		else if (i >= cycle_cnt * 0.25 && i < cycle_cnt * 0.5)
			$("#cycleAll_sector").css("border-right", "70px solid lime");
		else if (i >= cycle_cnt * 0.5 && i < cycle_cnt * 0.75)
			$("#cycleAll_sector").css("border-bottom", "70px solid lime");
		else if (i >= cycle_cnt * 0.75)
			$("#cycleAll_sector").css("border-left", "70px solid lime");
		if (i < cycle_cnt * 0.1)
		{
			$("#cycleAll_sector").css("border-top", "70px solid transparent");
			$("#cycleAll_sector").css("border-left", "70px solid transparent");
			$("#cycleAll_sector").css("border-bottom", "70px solid transparent");
			$("#cycleAll_sector").css("border-right", "70px solid transparent");
		}
	}

	draw_ctd();
	draw_cycle();
	
	player_n = 0;
	cnt = 0;
	idx = 2;

	while (player_n < players)
	{
		cnt = 0;
		idx = 2;
		while (idx < cycle[i][0].length)
		{
			if (champion[player_n][2] == cycle[i][0][idx])
				cnt = cnt + cycle[i][0][idx - 2];
			idx = idx + oper_step;
		}
		document.getElementById("player_bar" + player_n).innerHTML = "";
		cnt++;
		if (cnt > 87)
			cnt = 87;
		$("#player_bar" + player_n).css("width", cnt * 5 + "px");
		$("#player_bar" + player_n).append(cnt);
		player_n++;
	}
	i++;
	if (i == cycle_cnt - 1)
	{
		step = 3;
		clearInterval(warIntervalID);
		$("#game_over").slideToggle("slow", "linear");
		print_str(warFin_msg, 2);
		print_str("∘ the winner is: " + winner.substring(0, 20), 3);
		document.getElementById('audio_main').muted = true;
	}
}
