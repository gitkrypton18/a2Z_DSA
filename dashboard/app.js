/* ═══════════════════════════════════════════════════════════
   a2Z DSA Tracker — Dashboard Application
   Renders charts, patterns, tables, filters, and heatmap
   ═══════════════════════════════════════════════════════════ */

;(function () {
  'use strict';

  const D = DSA_DATA;              // data.js must load first
  const ROWS_PER_PAGE = 30;
  let currentPage = 1;
  let filteredProblems = [];
  let sortCol = null;
  let sortAsc = true;

  /* ─── Initialization ────────────────────────────────── */
  document.addEventListener('DOMContentLoaded', () => {
    renderSyncBadge();
    renderStatsOverview();
    renderDiffBars();
    renderTopicProgress();
    renderPatternCards();
    populateFilterDropdowns();
    applyFilters();                // renders table
    renderHeatmap();
    bindEvents();

    // Animate bars after a tick so transitions fire
    requestAnimationFrame(() => {
      requestAnimationFrame(() => {
        animateBars();
        animateRing();
      });
    });
  });

  /* ─── Sync Badge ────────────────────────────────────── */
  function renderSyncBadge() {
    const el = document.getElementById('syncBadge');
    if (D.meta && D.meta.lastSynced) {
      const d = new Date(D.meta.lastSynced);
      el.textContent = `Last synced: ${d.toLocaleDateString()} ${d.toLocaleTimeString([], {hour:'2-digit', minute:'2-digit'})}`;
    }
  }

  /* ─── Stats Overview ────────────────────────────────── */
  function renderStatsOverview() {
    const s = D.summary;
    document.getElementById('solvedCount').textContent = s.solved;
    document.getElementById('totalCount').textContent = `out of ${s.total}`;
    document.getElementById('ringPct').textContent = `${s.percentage}%`;

    // Topics
    const activeTops = D.topics.filter(t => t.solved > 0).length;
    document.getElementById('topicCount').textContent = activeTops;
    document.getElementById('topicSub').textContent = `of ${D.topics.length} topics`;

    // Patterns
    const activePats = D.patterns.filter(p => p.solved > 0).length;
    document.getElementById('patternCount').textContent = activePats;
  }

  function animateRing() {
    const ring = document.getElementById('progressRing');
    const circumference = 2 * Math.PI * 52; // r=52
    const pct = D.summary.percentage / 100;
    ring.style.strokeDashoffset = circumference * (1 - pct);
  }

  /* ─── Difficulty Bars ───────────────────────────────── */
  function renderDiffBars() {
    const container = document.getElementById('diffBars');
    const diffs = [
      { label: 'Easy',   data: D.summary.difficulty.easy,   color: '#22c55e' },
      { label: 'Medium', data: D.summary.difficulty.medium, color: '#f59e0b' },
      { label: 'Hard',   data: D.summary.difficulty.hard,   color: '#ef4444' },
    ];

    container.innerHTML = diffs.map(d => {
      const pct = d.data.total > 0 ? (d.data.solved / d.data.total * 100) : 0;
      return `
        <div class="diff-bar-row">
          <span class="diff-bar-label" style="color:${d.color}">${d.label}</span>
          <div class="diff-bar-track">
            <div class="diff-bar-fill" data-width="${pct}" style="background:${d.color}"></div>
          </div>
          <span class="diff-bar-count">${d.data.solved}/${d.data.total}</span>
        </div>`;
    }).join('');
  }

  function animateBars() {
    document.querySelectorAll('[data-width]').forEach(el => {
      el.style.width = el.dataset.width + '%';
    });
  }

  /* ─── Topic Progress ────────────────────────────────── */
  function renderTopicProgress() {
    const grid = document.getElementById('topicGrid');
    grid.innerHTML = D.topics.map(t => {
      const pct = t.total > 0 ? (t.solved / t.total * 100) : 0;
      return `
        <div class="topic-row glass">
          <span class="topic-name">${t.name}</span>
          <div class="topic-bar-track">
            <div class="topic-bar-fill" data-width="${pct.toFixed(1)}"></div>
          </div>
          <span class="topic-count">${t.solved}/${t.total}</span>
        </div>`;
    }).join('');
  }

  /* ─── Pattern Cards ─────────────────────────────────── */
  function renderPatternCards() {
    const grid = document.getElementById('patternGrid');
    grid.innerHTML = D.patterns.map(p => {
      const pct = p.total > 0 ? (p.solved / p.total * 100) : 0;
      return `
        <div class="pattern-card glass" data-pattern-id="${p.id}"
             style="--card-color: ${p.color}">
          <style>.pattern-card[data-pattern-id="${p.id}"]::before{background:${p.color}}</style>
          <span class="pattern-emoji">${p.emoji}</span>
          <div class="pattern-name">${p.name}</div>
          <div class="pattern-desc">${p.description}</div>
          <div class="pattern-progress">
            <div class="pattern-bar-track">
              <div class="pattern-bar-fill" data-width="${pct.toFixed(1)}" style="background:${p.color}"></div>
            </div>
            <span class="pattern-stats">${p.solved}/${p.total}</span>
          </div>
        </div>`;
    }).join('');
  }

  /* ─── Pattern Modal ─────────────────────────────────── */
  function openModal(patternId) {
    const p = D.patterns.find(x => x.id === patternId);
    if (!p) return;

    document.getElementById('modalTitle').textContent = `${p.emoji} ${p.name}`;
    document.getElementById('modalWhen').innerHTML = `<strong>When to use:</strong> ${p.whenToUse}`;

    const list = document.getElementById('modalProblems');
    if (p.problems.length === 0) {
      list.innerHTML = '<li style="padding:12px 0;color:var(--text-muted)">No problems tagged with this pattern yet.</li>';
    } else {
      list.innerHTML = p.problems.map(prob => {
        const diffClass = prob.difficulty.toLowerCase();
        const link = prob.link
          ? `<a href="${prob.link}" target="_blank" rel="noopener">${prob.name}</a>`
          : `<span>${prob.name}</span>`;
        return `
          <li class="modal-problem">
            <span class="modal-status">${prob.solved ? '✅' : '⬜'}</span>
            ${link}
            <span class="modal-diff ${diffClass}">${prob.difficulty}</span>
          </li>`;
      }).join('');
    }

    document.getElementById('modalOverlay').classList.add('active');
  }

  function closeModal() {
    document.getElementById('modalOverlay').classList.remove('active');
  }

  /* ─── Filter Dropdowns ──────────────────────────────── */
  function populateFilterDropdowns() {
    // Patterns
    const patternSelect = document.getElementById('patternFilter');
    D.patterns.forEach(p => {
      if (p.total > 0) {
        const opt = document.createElement('option');
        opt.value = p.name;
        opt.textContent = `${p.emoji} ${p.name} (${p.solved}/${p.total})`;
        patternSelect.appendChild(opt);
      }
    });

    // Topics
    const topicSelect = document.getElementById('topicFilter');
    const topicNames = [...new Set(D.problems.map(p => p.topic))].sort();
    topicNames.forEach(t => {
      if (t) {
        const opt = document.createElement('option');
        opt.value = t;
        opt.textContent = t;
        topicSelect.appendChild(opt);
      }
    });
  }

  /* ─── Apply Filters ─────────────────────────────────── */
  function applyFilters() {
    const query   = document.getElementById('searchInput').value.toLowerCase().trim();
    const diff    = document.getElementById('diffFilter').value;
    const pattern = document.getElementById('patternFilter').value;
    const topic   = document.getElementById('topicFilter').value;
    const status  = document.getElementById('statusFilter').value;

    filteredProblems = D.problems.filter(p => {
      if (query && !p.name.toLowerCase().includes(query)) return false;
      if (diff && p.difficulty !== diff) return false;
      if (pattern && !p.pattern.toLowerCase().includes(pattern.toLowerCase())) return false;
      if (topic && p.topic !== topic) return false;
      if (status === 'solved' && !p.solved) return false;
      if (status === 'unsolved' && p.solved) return false;
      return true;
    });

    // Apply sort
    if (sortCol) {
      filteredProblems.sort((a, b) => {
        let va = a[sortCol], vb = b[sortCol];
        if (typeof va === 'boolean') { va = va ? 1 : 0; vb = vb ? 1 : 0; }
        if (typeof va === 'string') { va = va.toLowerCase(); vb = vb.toLowerCase(); }
        if (va < vb) return sortAsc ? -1 : 1;
        if (va > vb) return sortAsc ? 1 : -1;
        return 0;
      });
    }

    currentPage = 1;
    renderTable();
  }

  /* ─── Render Table ──────────────────────────────────── */
  function renderTable() {
    const tbody = document.getElementById('problemBody');
    const start = (currentPage - 1) * ROWS_PER_PAGE;
    const page  = filteredProblems.slice(start, start + ROWS_PER_PAGE);

    tbody.innerHTML = page.map(p => {
      const diffClass = p.difficulty.toLowerCase();
      const link = p.link
        ? `<a href="${p.link}" target="_blank" rel="noopener">${p.name}</a>`
        : p.name;
      return `
        <tr>
          <td class="problem-name-cell">${link}</td>
          <td style="font-size:0.72rem;color:var(--text-muted)">${p.topic}</td>
          <td><span class="diff-badge ${diffClass}">${p.difficulty}</span></td>
          <td class="pattern-tag" title="${p.pattern}">${p.pattern}</td>
          <td class="status-icon">${p.solved ? '✅' : '⬜'}</td>
        </tr>`;
    }).join('');

    // Info
    const solved = filteredProblems.filter(p => p.solved).length;
    document.getElementById('tableInfo').textContent =
      `Showing ${start + 1}–${Math.min(start + ROWS_PER_PAGE, filteredProblems.length)} of ${filteredProblems.length} problems (${solved} solved)`;

    renderPagination();
  }

  /* ─── Pagination ────────────────────────────────────── */
  function renderPagination() {
    const totalPages = Math.ceil(filteredProblems.length / ROWS_PER_PAGE);
    const container = document.getElementById('pagination');

    if (totalPages <= 1) { container.innerHTML = ''; return; }

    let html = '';
    html += `<button class="page-btn" ${currentPage === 1 ? 'disabled' : ''} data-page="${currentPage - 1}">‹</button>`;

    const start = Math.max(1, currentPage - 2);
    const end   = Math.min(totalPages, currentPage + 2);

    if (start > 1) {
      html += `<button class="page-btn" data-page="1">1</button>`;
      if (start > 2) html += `<span style="color:var(--text-muted);padding:0 4px">…</span>`;
    }

    for (let i = start; i <= end; i++) {
      html += `<button class="page-btn ${i === currentPage ? 'active' : ''}" data-page="${i}">${i}</button>`;
    }

    if (end < totalPages) {
      if (end < totalPages - 1) html += `<span style="color:var(--text-muted);padding:0 4px">…</span>`;
      html += `<button class="page-btn" data-page="${totalPages}">${totalPages}</button>`;
    }

    html += `<button class="page-btn" ${currentPage === totalPages ? 'disabled' : ''} data-page="${currentPage + 1}">›</button>`;
    container.innerHTML = html;
  }

  /* ─── Heatmap ───────────────────────────────────────── */
  function renderHeatmap() {
    const wrap = document.getElementById('heatmapWrap');
    if (!D.commitDates || D.commitDates.length === 0) {
      wrap.innerHTML = '<div style="padding:12px;color:var(--text-muted);font-size:0.8rem">No commit data available. Run sync to populate.</div>';
      return;
    }

    // Build date → count map
    const dateCount = {};
    D.commitDates.forEach(d => {
      dateCount[d] = (dateCount[d] || 0) + 1;
    });

    // Build 52 weeks of data ending today
    const today = new Date();
    const startDate = new Date(today);
    startDate.setDate(startDate.getDate() - 364);
    // Adjust to start on Sunday
    startDate.setDate(startDate.getDate() - startDate.getDay());

    const weeks = [];
    const months = [];
    let currentMonth = -1;
    let weekDays = [];
    const cursor = new Date(startDate);

    while (cursor <= today) {
      const key = cursor.toISOString().slice(0, 10);
      const count = dateCount[key] || 0;
      const level = count === 0 ? '' : count <= 1 ? 'l1' : count <= 2 ? 'l2' : count <= 3 ? 'l3' : 'l4';
      const dayOfWeek = cursor.getDay();

      if (dayOfWeek === 0 && weekDays.length > 0) {
        weeks.push(weekDays);
        weekDays = [];
      }

      // Track months
      if (cursor.getMonth() !== currentMonth) {
        currentMonth = cursor.getMonth();
        months.push({ week: weeks.length, name: cursor.toLocaleString('default', { month: 'short' }) });
      }

      weekDays.push({ key, count, level, day: dayOfWeek });
      cursor.setDate(cursor.getDate() + 1);
    }
    if (weekDays.length > 0) weeks.push(weekDays);

    // Render months bar
    let monthsHtml = '<div class="heatmap-months" style="margin-left:0">';
    let lastWeek = -1;
    months.forEach(m => {
      if (m.week !== lastWeek) {
        const offset = m.week * 16; // 13px + 3px gap
        monthsHtml += `<span style="position:absolute;left:${offset}px">${m.name}</span>`;
        lastWeek = m.week;
      }
    });
    monthsHtml += '</div>';

    // Render weeks
    let heatmapHtml = `<div style="position:relative;padding-top:20px">${monthsHtml}<div class="heatmap">`;
    weeks.forEach(week => {
      heatmapHtml += '<div class="heatmap-week">';
      // Pad start of first week
      for (let d = 0; d < 7; d++) {
        const dayData = week.find(w => w.day === d);
        if (dayData) {
          heatmapHtml += `<div class="heatmap-day ${dayData.level}" title="${dayData.key}: ${dayData.count} commits"></div>`;
        } else {
          heatmapHtml += `<div class="heatmap-day" style="visibility:hidden"></div>`;
        }
      }
      heatmapHtml += '</div>';
    });
    heatmapHtml += '</div></div>';

    wrap.innerHTML = heatmapHtml;
  }

  /* ─── Event Binding ─────────────────────────────────── */
  function bindEvents() {
    // Filters
    document.getElementById('searchInput').addEventListener('input', debounce(applyFilters, 200));
    document.getElementById('diffFilter').addEventListener('change', applyFilters);
    document.getElementById('patternFilter').addEventListener('change', applyFilters);
    document.getElementById('topicFilter').addEventListener('change', applyFilters);
    document.getElementById('statusFilter').addEventListener('change', applyFilters);

    // Pattern cards → modal
    document.getElementById('patternGrid').addEventListener('click', e => {
      const card = e.target.closest('.pattern-card');
      if (card) openModal(parseInt(card.dataset.patternId, 10));
    });

    // Modal close
    document.getElementById('modalClose').addEventListener('click', closeModal);
    document.getElementById('modalOverlay').addEventListener('click', e => {
      if (e.target === e.currentTarget) closeModal();
    });
    document.addEventListener('keydown', e => { if (e.key === 'Escape') closeModal(); });

    // Table sort
    document.querySelectorAll('.problem-table thead th[data-sort]').forEach(th => {
      th.addEventListener('click', () => {
        const col = th.dataset.sort;
        if (sortCol === col) { sortAsc = !sortAsc; }
        else { sortCol = col; sortAsc = true; }
        applyFilters();
      });
    });

    // Pagination
    document.getElementById('pagination').addEventListener('click', e => {
      const btn = e.target.closest('.page-btn');
      if (btn && !btn.disabled) {
        currentPage = parseInt(btn.dataset.page, 10);
        renderTable();
        document.getElementById('problemSection').scrollIntoView({ behavior: 'smooth', block: 'start' });
      }
    });
  }

  /* ─── Utilities ─────────────────────────────────────── */
  function debounce(fn, ms) {
    let t;
    return function (...args) { clearTimeout(t); t = setTimeout(() => fn.apply(this, args), ms); };
  }

})();
