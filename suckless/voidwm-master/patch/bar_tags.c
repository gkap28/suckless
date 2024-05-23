int
width_tags(Bar *bar, BarWidthArg *a)
{
	int w, i;

	for (w = 0, i = 0; i < LENGTH(tags); i++) {
		w += TEXTW(tags[i]);
	}
	return w;
}

int
draw_tags(Bar *bar, BarDrawArg *a)
{
	int invert;
	int w, x = a->x;
	unsigned int i, occ = 0, urg = 0;
	Client *c;
	Monitor *m = bar->mon;

	for (c = m->clients; c; c = c->next) {
		occ |= c->tags;
		if (c->isurgent)
			urg |= c->tags;
	}

	for (i = 0; i < LENGTH(tags); i++) {
		invert = urg & 1 << i;
		w = TEXTW(tags[i]);
		/* rainbowtags if enabled and tag occupied (otherwise SchemeSel); SchemeNorm if tag selected and empty; SchemeTag for rest empty & inactive tags */
		drw_setscheme(drw, scheme[occ & 1 << i ? (rainbowtags ? tagschemes[i] : SchemeSel) : (m->tagset[m->seltags] & 1 << i ? SchemeNorm : SchemeTag)]);
		drw_text(drw, x, 0, w, bh, lrpad / 2, tags[i], invert);
		/* underline on active occupied tag only */
		if ((m->tagset[m->seltags] & 1 << i) && (occ & 1 << i))
			drw_rect(drw, x + ulinepad, bh - ulinestroke - ulinevoffset, w - (ulinepad * 2), ulinestroke, 1, invert);
		x += w;
	}

	return x;
}

int
click_tags(Bar *bar, Arg *arg, BarClickArg *a)
{
	int i = 0, x = lrpad / 2;

	do {
		x += TEXTW(tags[i]);
	} while (a->rel_x >= x && ++i < LENGTH(tags));
	if (i < LENGTH(tags)) {
		arg->ui = 1 << i;
	}
	return ClkTagBar;
}
